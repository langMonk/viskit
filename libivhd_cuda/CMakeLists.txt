cmake_minimum_required(VERSION 3.15)
project(libivhd_cuda CUDA)

set(CMAKE_CXX_STANDARD 17)


add_library(libivhd_cuda
        include/caster_factory.h
        include/constants.h
        include/distance_container.h
        include/distance.h
        include/caster/caster_cuda.cuh
        include/caster/caster_cuda_ab.cuh
        source/caster/caster_cuda.cu
        source/caster/caster_cuda_ab.cu)

# include ivhd
target_include_directories(libivhd_cuda PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(libivhd_cuda PRIVATE ${PROJECT_SOURCE_DIR}/../libivhd/include)
target_include_directories(libivhd_cuda PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)

target_link_directories(libivhd_cuda PRIVATE ${PROJECT_SOURCE_DIR}/../libivhd/cmake-build-debug)

target_link_libraries(libivhd_cuda libivhd)
