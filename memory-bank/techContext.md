# Technical Context: Paint

## Technologies Used
- **Language**: C++17
- **Compiler**: clang++ (Apple LLVM version 15.0.0 or similar)
- **Build System**: CMake (3.20+)
- **Graphics Library**: SFML 3.0.0 (Installed via Homebrew)
- **Platform**: macOS 14.x (Sonoma) on ARM64 (M1/M2/M3)

## Development Setup
- **Homebrew**: Used for managing dependencies like SFML.
- **VS Code**: Primary editor with C++ and CMake extensions.
- **Terminal**: zsh/bash for executing build commands.

## Technical Constraints
- Must be compatible with macOS ARM64 architecture.
- SFML 3.0.0 has some API differences compared to 2.6 (e.g., `sf::RenderWindow` usage, event handling).
- CMake must be able to find SFML installed in `/usr/local/Cellar/sfml/3.0.0` or via standard Homebrew paths.

## Tool Usage Patterns
- `cmake -B build`: Generate build files.
- `cmake --build build`: Compile the project.
- `./build/Paint`: Run the application.