cmake_minimum_required(VERSION 3.16)
project(RepositoryContextManager VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(repoctx
src/main.cpp	
 "src/cli.hpp" "src/cli.cpp" "src/fs_travel.hpp" "src/fs_travel.cpp")