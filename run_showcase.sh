#!/bin/bash

# Ensure script stops on error
set -e

echo "Rebuilding project for Linux..."

# Use the centralized build script
./tools/build_project.sh

echo ""
echo "Starting WebCee Showcase..."
./examples/showcase/showcase
