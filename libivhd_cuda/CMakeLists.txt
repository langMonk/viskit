cmake_minimum_required(VERSION 3.15)

project(libivhd_cuda CUDA)

find_package(CUDA REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -O3 -gencode arch=compute_75,code=sm_75 -maxrregcount=40")

add_library(libivhd_cuda
    include/caster/CasterCuda.h
    include/caster/CasterCudaAB.h
    include/caster/CasterCudaAdadelta.h
    include/caster/CasterCudaAdam.h
    include/GpuFactory.h
    include/caster/CasterCudaNesterov.h
    include/caster/Constants.h
    include/caster/InternalStructures.h
    include/ivhd_cuda/IGpuFactory.h
    src/caster/CasterCuda.cu
    src/caster/CasterCudaAB.cu
    src/caster/CasterCudaAdadelta.cu
    src/caster/CasterCudaAdam.cu
    src/caster/CasterCudaNesterov.cu
    src/GpuFactory.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libivhd/include/)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries/)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/third_party)
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDA_INCLUDE_DIRS})
