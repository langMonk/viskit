cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(viskit
        VERSION 0.5.1
        DESCRIPTION "A library for interactive visualization of high-dimensional data."
        HOMEPAGE_URL "https://gitlab.com/bminch/viskit"
        LANGUAGES CXX)

include(GNUInstallDirs)

# set(CMAKE_CXX_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++)

set(VISKIT_VERSION 0.5.1)
set(CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden" )

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


# maybe in future there will be some next optimization level (e.g. "avx")
option(VISKIT_OPT_LEVEL "" "generic")
option(VISKIT_ENABLE_PYTHON "Build Python extension." ON)

add_subdirectory(viskit)
add_subdirectory(viskit_offline)

if(VISKIT_ENABLE_PYTHON)
    add_subdirectory(viskit/python)
endif()

# CTest must be included in the top level to enable `make test` target.
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(viskit_tests)
endif()
