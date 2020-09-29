cmake_minimum_required(VERSION 3.15)
project(viskit)

set(VISKIT_VERSION 0.5.0)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(libviskit)
add_subdirectory(libviskit_tests)
add_subdirectory(QtEditor)
# add_subdirectory(viskit_experiments)
