#ifndef WEBCEE_DIAGNOSTIC_H
#define WEBCEE_DIAGNOSTIC_H

#include <stdarg.h>

typedef enum {
    DIAG_ERROR,   // Error, compilation aborted
    DIAG_WARNING, // Warning, compilation continues
    DIAG_INFO,    // Information
    DIAG_DEBUG    // Debug information (debug mode only)
} DiagnosticLevel;

typedef struct {
    char* file_name;         // Source file name
    int line;                // 1-based line number (starts from 1)
    int column;              // 1-based column number (starts from 1)
    DiagnosticLevel level;
    int error_code;          // Unique error code
    char message[256];       // Human-readable message
} Diagnostic;

typedef struct {
    Diagnostic* items;       // Diagnostic items array
    int capacity;            // Array capacity
    int count;               // Current count
    int error_count;         // Error count
} DiagnosticBag;

// Create and destroy diagnostic bag
DiagnosticBag* diagnostic_bag_create(void);
void diagnostic_bag_destroy(DiagnosticBag* bag);

// Report diagnostic information
void diagnostic_report(DiagnosticBag* bag,
                      const char* file_name,
                      int line, int column,
                      DiagnosticLevel level,
                      int error_code,
                      const char* fmt, ...);

// Print all diagnostic information to stderr
void diagnostic_print_all(const DiagnosticBag* bag);

// Check if any errors exist
int diagnostic_has_errors(const DiagnosticBag* bag);

#endif // WEBCEE_DIAGNOSTIC_H
