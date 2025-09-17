cmake_minimum_required(VERSION 3.20)
project(repoctx VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(repoctx
    src/main.cpp
    src/cli.cpp
    src/fs_travel.cpp
    src/git_info.cpp
    src/renderer.cpp
    src/utils.cpp)

target_include_directories(repoctx PRIVATE src include)


find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(LIBGIT2 libgit2)
endif()

if(LIBGIT2_FOUND)
    # Use system packages
    target_link_libraries(repoctx ${LIBGIT2_LIBRARIES})
    target_include_directories(repoctx PRIVATE ${LIBGIT2_INCLUDE_DIRS})
    target_compile_options(repoctx PRIVATE ${LIBGIT2_CFLAGS_OTHER})
    message(STATUS "Using system libgit2")
else()

    find_package(libgit2 CONFIG REQUIRED)
    target_link_libraries(repoctx libgit2::libgit2package)
    message(STATUS "Using vcpkg libgit2")
endif()

if(WIN32)
    target_compile_definitions(repoctx PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

install(TARGETS repoctx RUNTIME DESTINATION bin)