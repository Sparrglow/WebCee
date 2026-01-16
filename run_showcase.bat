@echo off
echo Rebuilding project to ensure latest changes...
call build.bat
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

echo.
echo Starting WebCee Showcase...
echo.
"build\Release\showcase.exe"
