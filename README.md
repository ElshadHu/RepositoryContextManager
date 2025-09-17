# RepositoryContextPackager
Command-line tool that analyzes  local git repositories and creates a text file containing repository content optimized for sharing with Large Language Models (LLMs).This tool helps developers efficiently share their codebase context with Ai tools such as ChatGPT via collection repository information,project structure and file contents into a single, well-designed document.

# Features
- **Git Integration** - Automatically detects Git repository information (commit, branch, author, date)
- **Smart File Discovery** - Recursively analyzes directories and individual files
- **Multiple File Type Support** - Handles C/C++, JavaScript, Python, Java, TypeScript, and configuration files
- **Error Handling** - Gracefully handles permission errors and inaccessible files
- **File Size Management** - Automatically truncates large files (>16KB) with truncation notices
- **Flexible Input** - Supports analyzing directories, individual files, or combinations

# Prerequisites
- CMake 3.20 or higher
- C++17 compatible compiler
- Git(for repository analysis features)
# Installation

# 1. Install vcpkg and dependencies

# Clone vcpkg (if not already installed)
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat  # Windows
set VCPKG_ROOT=%CD%
# Install libgit2
```
# Install libgit2
```bash
.\vcpkg install libgit2
```
# 2. Build the project
## Clone this repository
```bash
git clone [your-repo-url]
cd RepositoryContextPackager
cmake --preset default
cmake --build build --config Release
```
# Linux
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake libgit2-dev pkg-config git

# Build 
git clone <your-repo-url>
cd RepositoryContextPackager
cmake --preset default
cmake --build build
```

# macOS
```bash
# Install dependencies
brew install cmake libgit2 pkg-config git

# Build 
git clone <your-repo-url>
cd RepositoryContextPackager
cmake --preset default
cmake --build build
```
# Usage
# Basic Commands
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
repoctx src docs examples

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
# Repository Context

## File System Location
/absolute/path/to/analyzed/location

### GIT INFO
- Commit: e45f8911e2ca40223faf2309bf1996443f2df336
- Branch: main
- Author: Your Name <your.email@example.com>
- Date: Thu Sep 12 16:07:19 2025

## Structure
include/
utils.hpp
src/
   main.cpp
   cli.cpp
   cli.hpp
CMakeLists.txt
```
### File: src/main.cpp

```cpp
#include <iostream>
int main() {
    std::cout << "Hi There!" << std::endl;
    return 0;
}

Total Files: 15
Total Lines: 1,247
Total Tokens: 4,532
```

# Testing from Source

```bash
# Configure for development
cmake --preset default

# Build
cmake --build build --config Release

# Test locally
./build/Release/repoctx --help    # Linux/macOS
.\build\Release\repoctx.exe --help # Windows

```

## Project Structure
``` bash
RepositoryContextPackager/
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
├── CMakePresets.json     # Build presets
├── vcpkg.json           # Dependencies
└── README.md            # This file           
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


