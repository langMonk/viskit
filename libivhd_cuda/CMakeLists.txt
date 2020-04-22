cmake_minimum_required(VERSION 3.15)

project(libivhd_cuda CUDA)

find_package(CUDA REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -arch sm_75 -std=c++11 -Wno-deprecated-gpu-targets -maxrregcount=40")

add_library(${PROJECT_NAME}
    include/caster/caster.h
    include/caster/caster_cuda.h
    include/caster/caster_cuda_ab.h
    include/caster/caster_cuda_adadelta.h
    include/caster/caster_cuda_adam.h
    include/caster/caster_cuda_nesterov.h
    include/Clock.h
    include/constants.h
    include/data.h
    include/distance_container.h
    include/distance.h
    include/knn_parser.h
    src/caster/caster_cuda.cu
    src/caster/caster_cuda_ab.cu
    src/caster/caster_cuda_adadelta.cu
    src/caster/caster_cuda_adam.cu
    src/caster/caster_cuda_nesterov.cu
    src/data.cpp
    src/knn_parser.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/third_party)
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDA_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME})