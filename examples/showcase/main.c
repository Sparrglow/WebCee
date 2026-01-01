#include "webcee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SERVER_PORT 8080

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")
#define sleep_ms(x) Sleep(x)
#else
#include <unistd.h>
#define sleep_ms(x) usleep((x)*1000)
#endif

extern void wce_ui_main(void);

// --- State ---
static int counter = 0;
static int cpu_load = 0;
static int mem_load = 0;
static int active_connections = 0;
static char last_log[256] = "System Ready.";

// --- Logic ---

void update_dashboard() {
    char buf[32];
    
    // Update Counter
    sprintf(buf, "%d", counter);
    wce_data_set("counter_val", buf);
    
    sprintf(buf, "%d", active_connections);
    wce_data_set("active_conn", buf);
    
    // CPU load is proportional to active connections + random noise
    int target_cpu = active_connections * 5; 
    if (target_cpu > 100) target_cpu = 100;
    
    // Smooth transition
    if (cpu_load < target_cpu) cpu_load++;
    else if (cpu_load > target_cpu) cpu_load--;
    
    // Real Memory Usage
    #ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        mem_load = (int)(pmc.WorkingSetSize / 1024 / 1024);
    } else {
        mem_load = 0;
    }
    #else
    // Linux: Read /proc/self/statm (resident set size is the 2nd field, in pages)
    FILE* f = fopen("/proc/self/statm", "r");
    if (f) {
        long size, resident, share, text, lib, data, dt;
        if (fscanf(f, "%ld %ld %ld %ld %ld %ld %ld", &size, &resident, &share, &text, &lib, &data, &dt) == 7) {
            long page_size_kb = sysconf(_SC_PAGESIZE) / 1024;
            mem_load = (int)((resident * page_size_kb) / 1024);
        }
        fclose(f);
    } else {
        mem_load = 0;
    }
    #endif
    
    sprintf(buf, "%d%%", cpu_load);
    wce_data_set("cpu_val", buf);
    
    sprintf(buf, "%d MB", mem_load);
    wce_data_set("mem_val", buf);
}

// Hook for input changes
void wce_handle_model_update(const char* key, const char* val) {
    if (strcmp(key, "user_input") == 0) {
        // Demonstrate C string processing
        int len = strlen(val);
        char response[512];
        
        // Reverse string logic
        char reversed[256];
        strncpy(reversed, val, 255);
        reversed[255] = '\0';
        for(int i=0, j=strlen(reversed)-1; i<j; i++, j--) {
            char t = reversed[i]; reversed[i] = reversed[j]; reversed[j] = t;
        }
        
        snprintf(response, sizeof(response), 
            "Length=%d, Reversed='%s' (Processed in C)", 
            len, reversed);
            
        wce_data_set("server_response", response);
        
        // Update log
        snprintf(last_log, sizeof(last_log), "> Received input: %s", val);
        wce_data_set("server_log", last_log);
        
        // Print to terminal as requested
        printf("[Terminal] Received User Input: %s\n", val);
    }
}

void on_inc() {
    active_connections++;
    counter++;
    snprintf(last_log, sizeof(last_log), "> New Connection! Active: %d", active_connections);
    wce_data_set("server_log", last_log);
    update_dashboard();
    printf("[Action] Connection added. Active: %d\n", active_connections);
}

void on_reset() {
    active_connections = 0;
    counter = 0;
    strcpy(last_log, "> System Reset.");
    wce_data_set("server_log", last_log);
    wce_data_set("user_input", "");
    wce_data_set("server_response", "Waiting for input...");
    update_dashboard();
    printf("[Action] System Reset\n");
}

int main() {
    srand((unsigned int)time(NULL));
    printf("Starting WebCee Showcase...\n");
    
    if (wce_init(SERVER_PORT) != 0) {
        printf("Failed to init WebCee\n");
        return 1;
    }
    
    // Register callbacks
    wce_register_function("on_inc", on_inc);
    wce_register_function("on_reset", on_reset);
    
    // Initial data
    cpu_load = 0;
    mem_load = 1024;
    update_dashboard();
    wce_data_set("user_input", "");
    wce_data_set("server_response", "Waiting for input...");
    wce_data_set("server_log", "> System Ready.");
    
    // Build UI
    wce_ui_main();
    
    printf("Server running at http://localhost:%d\n", SERVER_PORT);
    if (wce_start() != 0) {
        printf("Failed to start server\n");
        return 1;
    }
    
    printf("Press Enter to stop server...\n");
    getchar();
    
    wce_stop();
    return 0;
}
