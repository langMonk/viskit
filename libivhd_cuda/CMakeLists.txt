cmake_minimum_required(VERSION 3.15)

project(libivhd_cuda CUDA)

set(CMAKE_CXX_STANDARD 17)

find_package(CUDA REQUIRED)
find_package(Boost REQUIRED)

add_library(libivhd_cuda
    include/caster/CasterCuda.h
    include/caster/CasterCudaAB.h
    include/caster/CasterCudaAdadelta.h
    include/caster/CasterCudaAdam.h
    include/GpuFactory.h
    include/caster/CasterCudaNesterov.h
    include/caster/Constants.h
    include/caster/InternalStructures.h
    include/graph/FaissGraphGenerator.h
    include/ivhd_cuda/IGpuFactory.h
    src/caster/CasterCuda.cu
    src/caster/CasterCudaAB.cu
    src/caster/CasterCudaAdadelta.cu
    src/caster/CasterCudaAdam.cu
    src/caster/CasterCudaNesterov.cu
    src/graph/FaissGraphGenerator.cpp
    src/GpuFactory.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libviskit/include/ivhd)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries/)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/third_party)
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDA_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} faiss)
