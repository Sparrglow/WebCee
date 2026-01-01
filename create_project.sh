#!/bin/bash
set -e

# 1. Get path info
SRC_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TARGET_DIR="$1"

if [ -z "$TARGET_DIR" ]; then
    echo "Usage: ./create_project.sh [Path]"
    exit 1
fi

# Resolve absolute path for target
if [[ "$TARGET_DIR" != /* ]]; then
    TARGET_DIR="$PWD/$TARGET_DIR"
fi

echo "[WebCee] Target Project Path: $TARGET_DIR"

# 2. Check and build compiler
COMPILER_EXE="$SRC_ROOT/tools/wce"

if [ ! -f "$COMPILER_EXE" ]; then
    echo "[WebCee] Compiler binary not found. Building from source..."
    mkdir -p "$SRC_ROOT/tools"
    gcc $SRC_ROOT/compiler/core/*.c $SRC_ROOT/compiler/main.c -o "$COMPILER_EXE" -std=c11 -Wall -Wno-unused-function
    echo "[WebCee] Compiler built successfully."
fi

# 3. Create directory structure
mkdir -p "$TARGET_DIR/tools"
mkdir -p "$TARGET_DIR/lib"

# 4. Copy files
echo "[WebCee] Copying files..."
cp "$COMPILER_EXE" "$TARGET_DIR/tools/"
cp "$SRC_ROOT/src/webcee.c" "$TARGET_DIR/lib/"
cp "$SRC_ROOT/include/"*.h "$TARGET_DIR/lib/"

# 5. Generate ui.wce
cat > "$TARGET_DIR/ui.wce" <<EOF
wce_container() {
    wce_card() {
        wce_css("text-align: center; padding: 40px;");
        wce_row() {
            wce_text("Welcome to WebCee") {
                wce_css("display: block; font-size: 32px; font-weight: bold; color: #2c3e50; margin-bottom: 15px;");
            }
        }
        wce_row() {
            wce_text("High-Performance Embedded C Web Framework") {
                wce_css("display: block; font-size: 18px; color: #7f8c8d; margin-bottom: 30px;");
            }
        }
        wce_row() {
            wce_button("Click Me!") {
                wce_on_click("on_click");
                wce_css("background-color: #3498db; color: white; padding: 12px 24px; border: none; border-radius: 6px; font-size: 16px; cursor: pointer; transition: background 0.2s;");
            }
        }
        wce_row() {
            wce_text("Counter: 0") {
                wce_bind("counter_val");
                wce_css("display: block; margin-top: 20px; font-weight: bold; color: #2c3e50;");
            }
        }
    }
}
EOF

# 6. Generate main.c
cat > "$TARGET_DIR/main.c" <<EOF
#include "lib/webcee.h"
#include <stdio.h>

// Declare generated UI function
extern void wce_ui_main(void);

static int counter = 0;

void on_click() {
    counter++;
    char buf[32];
    sprintf(buf, "Counter: %d", counter);
    wce_data_set("counter_val", buf);
    printf("Button clicked! Counter: %d\n", counter);
}

int main() {
    if (wce_init(8080) != 0) {
        printf("Failed to init server\n");
        return 1;
    }

    wce_register_function("on_click", on_click);
    wce_data_set("counter_val", "Counter: 0");

    // Build UI
    wce_ui_main();

    printf("Server running at http://localhost:8080\n");
    if (wce_start() != 0) {
        printf("Failed to start server\n");
        return 1;
    }

    // Keep running
    while(1) {
        wce_sleep(1000);
    }

    wce_stop();
    return 0;
}
EOF

# 7. Generate build.sh
cat > "$TARGET_DIR/build.sh" <<EOF
#!/bin/bash
set -e

echo "Compiling UI..."
./tools/wce ui.wce ui_gen.c

echo "Compiling App..."
gcc -std=c11 main.c ui_gen.c lib/webcee.c -I lib -o app -lpthread

echo "Build complete! Run ./app"
EOF

chmod +x "$TARGET_DIR/build.sh"

echo ""
echo "[WebCee] Project created at $TARGET_DIR"
echo "  cd $TARGET_DIR"
echo "  ./build.sh"
echo ""
