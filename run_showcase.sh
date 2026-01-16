#!/bin/bash

# Ensure script stops on error
set -e

echo "Rebuilding project for Linux..."

# Use the centralized build script
./build.sh

echo ""
echo "Starting WebCee Showcase..."
./build/showcase
