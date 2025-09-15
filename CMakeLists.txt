cmake_minimum_required(VERSION 3.16)
project(RepositoryContextManager VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(repoctx
    src/main.cpp
    src/cli.cpp
    src/fs_travel.cpp
    src/git_info.cpp
 src/renderer.cpp
 src/utils.cpp)

# Include src directory for headers
target_include_directories(repoctx PRIVATE src)
target_include_directories(repoctx PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Windows-only manual libgit2 setup 
if(WIN32)
    target_include_directories(repoctx PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/installed/x64-windows/include"
    )
    target_link_libraries(repoctx PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/installed/x64-windows/lib/git2.lib"
    )
    target_compile_definitions(repoctx PRIVATE _CRT_SECURE_NO_WARNINGS)
    message(STATUS "Using manual libgit2 paths for Windows")
else()
   
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBGIT2 REQUIRED libgit2)
    target_link_libraries(repoctx PRIVATE ${LIBGIT2_LIBRARIES})
    target_include_directories(repoctx PRIVATE ${LIBGIT2_INCLUDE_DIRS})
    target_compile_options(repoctx PRIVATE ${LIBGIT2_CFLAGS_OTHER})
    message(STATUS "Using pkg-config libgit2 for Unix")
endif()