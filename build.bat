@echo off
setlocal enabledelayedexpansion

echo ========================================
echo   WebCee Build Script (Windows)
echo ========================================

echo Creating build directory...
if not exist "build" mkdir build

cd build

echo Configuring project with CMake...
cmake .. -G "Visual Studio 17 2022"

if errorlevel 1 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo Building project...
cmake --build . --config Release

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo ========================================
echo   Build completed successfully!
echo ========================================
echo.
echo Generated files in build\Release directory:
dir /b Release\*.exe Release\*.lib 2>nul

echo.
echo To run the showcase:
echo   cd build\Release
echo   showcase.exe
echo.
echo To use in your project:
echo   Copy include\ and lib\ directories to your project
echo   Link with webcee.lib

pause