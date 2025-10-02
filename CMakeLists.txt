cmake_minimum_required(VERSION 3.20)
project(repoctx VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding TOML fetch
include(FetchContent)
FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
  GIT_TAG v3.4.0 # or latest stable
)
FetchContent_MakeAvailable(tomlplusplus)

# if does not open try   link_directories("<Path-to-vcpkg>/installed/x64-windows/lib")

add_executable(repoctx
    src/main.cpp
    src/cli.cpp
    src/fs_travel.cpp
    src/git_info.cpp
    src/renderer.cpp
    src/utils.cpp
    src/filter.cpp )

target_include_directories(repoctx PRIVATE src include)

# Link toml++ to target
target_link_libraries(repoctx PRIVATE tomlplusplus)

# It tries to find system libgit2 
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(LIBGIT2 libgit2)
endif()

if(LIBGIT2_FOUND)
    # Use libgit2 which is system-installed
    target_link_libraries(repoctx ${LIBGIT2_LIBRARIES})
    target_include_directories(repoctx PRIVATE ${LIBGIT2_INCLUDE_DIRS})
    target_compile_options(repoctx PRIVATE ${LIBGIT2_CFLAGS_OTHER})
    message(STATUS "Using system libgit2")
else()
#  Go back to vcpkg libgit2(typical for Windows)
    find_package(libgit2 CONFIG REQUIRED)
    target_link_libraries(repoctx libgit2::libgit2package)
    message(STATUS "Using vcpkg libgit2")
endif()

# Windows related compiler stuff
if(WIN32)
    target_compile_definitions(repoctx PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

install(TARGETS repoctx RUNTIME DESTINATION bin)