# WebCee

A lightweight, C-based web UI framework for embedded systems.

## Features

- **Pure C Compiler**: No Python or Node.js dependencies.
- **Declarative UI**: Define UI in `.wce` files with a C-like syntax.
- **Rich Components**: Support for rows, columns, cards, panels, buttons, inputs, sliders, and progress bars.
- **Nested Layouts**: Support for complex nested UI structures.
- **Embedded Server**: Built-in HTTP server for serving the UI.

## Quick Start

### 1. Build the Project

WebCee uses CMake for cross-platform builds. Use the provided build scripts:

**Windows:**
```bat
.\build.bat
```

**Linux/macOS:**
```bash
./build.sh
```

This will:
- Configure the project with CMake
- Build the WebCee compiler (`wce_tool.exe`)
- Build the runtime library (`webcee.lib`)
- Build the showcase example (`showcase.exe`)

### 2. Run the Showcase

After building, run the showcase demo:

**Windows:**
```bat
cd build\Release
showcase.exe
```

**Linux/macOS:**
```bash
cd build
./showcase
```

Open your browser at `http://localhost:8080`.

### 3. Create a New Project

Use the included script to generate a ready-to-run project template:

```bat
.\create_project.bat MyNewApp
```

This will create a folder `MyNewApp` with:
- `ui.wce`: The UI layout definition.
- `main.c`: The application logic.
- `build.bat`: A script to compile and run your app.

## Examples

### Showcase Demo

The `examples/showcase` project demonstrates all core features of WebCee, including:
- **Layouts**: Rows, columns, cards, and panels.
- **Interactivity**: Buttons with C callback functions.
- **Data Binding**: Real-time text updates and input field binding.
- **Styling**: Custom CSS injection.

**To build and run the showcase:**

1. Build the entire project:
   ```bat
   .\build.bat
   ```

2. Run the showcase executable:
   ```bat
   cd build\Release
   showcase.exe
   ```

3. Open `http://localhost:8080` to interact with the demo.

## Project Structure

- `compiler/`: Source code for the `wce` compiler (converts `.wce` to C).
- `include/`: Header files (`webcee.h`, `webcee_build.h`).
- `src/`: Runtime library source (`webcee.c`).
- `examples/`: Example projects.
- `build.bat` / `build.sh`: One-click build scripts for the library and compiler.
- `create_project.bat` / `create_project.sh`: Project scaffolding tools.

## License

Apache License 2.0
