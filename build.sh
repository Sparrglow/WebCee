#!/bin/bash
set -e

echo "======================================="
echo "  WebCee Build Script (Linux/macOS)"
echo "======================================="

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR"

echo "Project root: $PROJECT_ROOT"

# Create build directory
BUILD_DIR="$PROJECT_ROOT/build"
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

echo "Configuring project with CMake..."
# Try different generators based on what's available
if command -v ninja >/dev/null 2>&1; then
    echo "Using Ninja generator..."
    cmake "$PROJECT_ROOT" -G "Ninja" -DCMAKE_BUILD_TYPE=Release
elif [ "$(uname)" = "Darwin" ]; then
    echo "Using Xcode generator on macOS..."
    cmake "$PROJECT_ROOT" -G "Xcode" -DCMAKE_BUILD_TYPE=Release
else
    echo "Using Unix Makefiles generator..."
    cmake "$PROJECT_ROOT" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
fi

echo "Building project..."
cmake --build . --config Release

echo ""
echo "======================================="
echo "  Build completed successfully!"
echo "======================================="
echo ""
echo "Generated files in build directory:"
ls -la Release/ 2>/dev/null || ls -la *.exe *.lib *.a 2>/dev/null || echo "Build files generated"

echo ""
echo "To run the showcase:"
echo "  cd build"
echo "  ./showcase  # or ./Release/showcase on macOS"
echo ""
echo "To use in your project:"
echo "  Copy include/ and lib/ directories to your project"
echo "  Link with webcee library"