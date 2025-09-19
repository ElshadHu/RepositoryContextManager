# RepositoryContextPackager
Command-line tool that analyzes  local git repositories and creates a text file containing repository content optimized for sharing with Large Language Models (LLMs).This tool helps developers efficiently share their codebase context with Ai tools such as ChatGPT via collection repository information,project structure and file contents into a single, well-designed document.

# Features
- **Git Integration** - Automatically detects Git repository information (commit, branch, author, date)
- **Smart File Discovery** - Recursively analyzes directories and individual files
- **Multiple File Type Support** - Handles C/C++, JavaScript, Python, Java, TypeScript, and configuration files
- **Error Handling** - Gracefully handles permission errors and inaccessible files
- **File Size Management** - Automatically truncates large files (>16KB) with truncation notices
- **Flexible Input** - Supports analyzing directories, individual files, or combinations
- **Include/Exclude Feature** Supports including or excluding specific folders or files

# Prerequisites
- CMake 3.20 or higher
- C++17 compatible compiler
- Git(for repository analysis features)
# Installation

# 1. Install vcpkg and dependencies

# Clone vcpkg  Windows (if not already installed)
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
$env:VCPKG_ROOT = $PWD

# Install libgit2 for Windows x64
.\vcpkg install libgit2:x64-windows
```
# 2. Build the project
## Clone this repository
```bash
git clone https://github.com/ElshadHu/RepositoryContextPackager
cd RepositoryContextPackager
# Method 1: Using environment variable (recommended)
cmake -B build -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake"
cmake --build build

# Method 2: Direct path (if vcpkg is in parent directory)
cmake -B build -DCMAKE_TOOLCHAIN_FILE="..\vcpkg\scripts\buildsystems\vcpkg.cmake"
cmake --build build

# Method 3: Without specifying toolchain (if vcpkg is configured globally)
cmake -B build
cmake --build build
```
# Linux
```bash
1.
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
chmod +x ./bootstrap-vcpkg.sh
./bootstrap-vcpkg.sh

2.
set VCPKG_ROOT=%CD%
chmod  +x ./vcpkg
./vcpkg install libgit2

3.
git clone   https://github.com/ElshadHu/RepositoryContextPackager
cd RepositoryContextPackager

cmake -G "Ninja" -B build
cmake --build build
```

# macOS
```bash
# Install dependencies
brew install cmake libgit2 pkg-config git

# Build 
git clone https://github.com/ElshadHu/RepositoryContextPackager
cd RepositoryContextPackager
cmake -B build
cmake --build build
```
# Usage
## Basic Commands
```bash
# Analyze current directory
repoctx .

# Analyze specific directory with output file
repoctx src --output report.md

# Include only specific file types
repoctx . --include "*.cpp,*.h,*.py"

# Exclude certain patterns
repoctx . --exclude "test,build,node_modules"

# Show help
repoctx --help

# Show version
repoctx --version
```

# Advanced Usage
```
# Analyze C++ project, excluding tests and build files
repoctx . --include "*.cpp,*.hpp,*.h" --exclude "test,build" --output cpp-analysis.md

# Analyze multiple directories
repoctx src docs 

# Mix files and directories
repoctx src README.md CMakeLists.txt --output project-overview.md
```

# Command Line Options
| Option           | Description                       | Example                          |
|------------------|-----------------------------------|----------------------------------|
| `--help`, `-h`    | Show help message                  | `repoctx -h`                     |
| `--version`, `-v` | Show version info                  | `repoctx -v`                     |
| `--output`, `-o`  | Output file path                   | `repoctx -o report.md`           |
| `--include`       | Include file extensions            | `--include "*.cpp,*.h"`           |
| `--exclude`       | Exclude file patterns               | `--exclude "test,build"`          |



# Output Format 
```markdown
PS D:\osdProjects\RepositoryContextPackager> .\build\repoctx.exe .
# Repository Context

## File System Location

D:\osdProjects\RepositoryContextPackager

### GIT INFO

- Commit: 4e96146d00cc70854c98e70caf5cf597553daca2
- Branch: main
- Author: Elshad Humbatli< elsadhumbetli079@gmail.com >
- Date: Thu Sep 18 02:30:16 2025

Structure

CMakeLists.txt
CMakeSettings.json
\include
    utils.hpp
LICENSE
README.md
\src
    cli.cpp
    cli.hpp
    fs_travel.cpp
    fs_travel.hpp
    git_info.cpp
    git_info.hpp
    main.cpp
    renderer.cpp
    renderer.hpp
    utils.cpp
vcpkg.json



### File:"CMakeLists.txt"
``` text
cmake_minimum_required(VERSION 3.20)
project(repoctx VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
  additional data is shown about files ...

  --  At the end file data
  Total Files: 15
Total Lines: 1,247
Total Tokens: 4,532

```


# Testing from Source

```bash


# Build
cmake --build build --config Release

# Test locally
./build/Release/repoctx --help    # Linux/macOS
.\build\Release\repoctx.exe --help # Windows

```

## Project Structure
``` bash
osdProjects/ # that is a local development directory
├── vcpkg/                          # C++ package manager
|     ├── scripts/buildsystems/vcpkg.cmake
│     └── [vcpkg installation files...] 
└── RepositoryContextPackager/      # This project
    ├── include/
    │   └── utils.hpp         # Utility function declarations
    ├── src/
    │   ├── main.cpp          # Main entry point
    │   ├── cli.cpp           # Command-line argument parsing
    │   ├── cli.hpp           # CLI parsing declarations
    │   ├── fs_travel.cpp     # File system traversal
    │   ├── fs_travel.hpp     # File system traversal declarations
    │   ├── git_info.cpp      # Git repository information
    │   ├── git_info.hpp      # Git info declarations
    │   ├── renderer.cpp      # Output rendering
    │   ├── renderer.hpp      # Renderer declarations
    │   └── utils.cpp         # Utility functions
    ├── CMakeLists.txt        # Build configuration
    ├── vcpkg.json           # Dependencies
    └── README.md            # README file            
```
# Contributing
- Fork the repository
- Create your feature branch (git checkout -b feature/recent)
- Commit your changes (git commit -m 'feature added')
- Push to the branch (git push origin feature/recent)
- Open a Pull Request


# License
This project is licensed under the MIT License - see the LICENSE file for details.


# Essentials
Built with libgit2 for Git repository access
Uses vcpkg for dependency management
Designed for integration with Large Language Models


