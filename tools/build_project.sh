#!/bin/bash
set -e

# Get absolute path to root
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

COMPILER_SRC="$ROOT/compiler/core/*.c $ROOT/compiler/main.c"
COMPILER_EXE="$ROOT/tools/wce"
SHOWCASE_DIR="$ROOT/examples/showcase"

echo "[1/3] Building WebCee Compiler..."
mkdir -p "$ROOT/tools"
gcc -std=c11 -Wall -Wextra -Wno-unused-function $COMPILER_SRC -o "$COMPILER_EXE"
echo "Compiler built at $COMPILER_EXE"

echo "[2/3] Compiling Showcase UI..."
"$COMPILER_EXE" "$SHOWCASE_DIR/ui.wce" "$SHOWCASE_DIR/ui_gen.c"

echo "[3/3] Building Showcase Application..."
gcc -std=c11 "$SHOWCASE_DIR/main.c" "$SHOWCASE_DIR/ui_gen.c" "$ROOT/src/webcee.c" -I "$ROOT/include" -o "$SHOWCASE_DIR/showcase" -lpthread

echo ""
echo "Build Complete!"
echo ""
echo "[Showcase]"
echo "  Run: $SHOWCASE_DIR/showcase"
echo ""
echo "[New Project]"
echo "  Run: ./create_project.sh MyNewApp"
echo ""
