# RepositoryContextManager
Command-line tool that analyzes  local git repositories and creates a text file containing repository content optimized for sharing with Large Language Models (LLMs).This tool helps developers efficiently share their codebase context with Ai tools such as ChatGPT via collection repository information,project structure and file contents into a single, well-designed document.

# Features
- **Git Integration**: Automatically detects Git repository information (commit, branch, author, date)
- **Smart File Discovery**: Recursively analyzes directories and individual files
- **Multiple File Type Support**: Handles C/C++, JavaScript, Python, Java, TypeScript, and configuration files
- **Error Handling**: Gracefully handles permission errors and inaccessible files
- **File Size Management**: Automatically truncates large files (>16KB) with truncation notices
- **Flexible Input**: Supports analyzing directories, individual files, or combinations

# Prerequisites
CMake 3.16 or higher
Microsoft vcpkg package manager
Visual Studio 2019/2022 or equivalent C++17 compiler
Git(for repository analysis features

# Installation

# 1. Install vcpkg and dependencies

# Clone vcpkg (if not already installed)
```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat  # Windows
./bootstrap-vcpkg.sh   # Linux/macOS
```
# Install libgit2
```bash
./vcpkg install libgit2:x64-windows
./vcpkg integrate install
```
# 2. Build the project
# Clone this repository
```bash
git clone [your-repo-url]
cd RepositoryContextManager
```
# Configure and build
```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build
```
# Usage
#Basic Commands

# Analyze current directory
```bash
repoctx .
```
# Analyze specific directory
```bash
repoctx src
```
# Analyze multiple directories
```bash
repoctx src docs tests
```
# Analyze specific files
```bash
repoctx main.cpp cli.hpp CMakeLists.txt
```
# Mix files and directories
```bash
repoctx src README.md CMakeLists.txt
```
# Show version
```bash
repoctx --version
```
# Show help
```bash
repoctx --help
```
# Output Format
The tool generates structured markdown output:
# Repository Context

## File System Location
```bash
/absolute/path/to/analyzed/location
```
## Git Info
```bash
- Commit: e45f8911e2ca40223faf2309bf1996443f2df336
- Branch: main
- Author:  Your name<yourmail@email.com>
- Date: Thu Aug 28 16:07:19 2025 -0400
```
## Structure
```bash
src/
main.cpp
cli.cpp
cli.hpp
CMakeLists.txt
```
# Development
#Project Structure
```bash
RepositoryContextManager/
├── src/
│   ├── main.cpp          # Main entry point
│   ├── cli.cpp/.hpp      # Command-line argument parsing
│   ├── fs_travel.cpp/.hpp # File system traversal and analysis
│   └── git_info.cpp/.hpp # Git repository information extraction
├── CMakeLists.txt        # Build configuration
└── README.md            # This file
```
# License
This project is licensed under the MIT License - see the LICENSE file for details.
#Contributing

# Essetials
Built with libgit2 for Git repository access
Uses vcpkg for dependency management
Designed for integration with Large Language Models


