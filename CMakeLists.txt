cmake_minimum_required(VERSION 3.15)
project(ivhd)

set(IVHD_VERSION 0.5.0)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory( libivhd )
add_subdirectory( libivhd_tests )
add_subdirectory( libivhd_cuda )
add_subdirectory( QtEditor )
