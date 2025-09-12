cmake_minimum_required(VERSION 3.16)
project(RepositoryContextManager VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(repoctx
    src/main.cpp
    src/cli.cpp
    src/fs_travel.cpp
    src/git_info.cpp
)

target_include_directories(repoctx PRIVATE 
    src
    "D:/osdProjects/vcpkg/installed/x64-windows/include"
)

target_link_libraries(repoctx PRIVATE 
    "D:/osdProjects/vcpkg/installed/x64-windows/lib/git2.lib"
)

if(WIN32)
    target_compile_definitions(repoctx PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
