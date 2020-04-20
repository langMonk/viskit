cmake_minimum_required(VERSION 3.15)
project(ivhd_cuda_standalone CUDA)

set(CMAKE_CXX_STANDARD 17)

find_package(CUDA REQUIRED)

add_executable(ivhd_cuda_standalone
        ivhd_cuda_standalone.cpp)

# include ivhd
target_include_directories(ivhd_cuda_standalone PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ivhd_cuda_standalone PRIVATE ${PROJECT_SOURCE_DIR}/../libivhd/include)
target_include_directories(ivhd_cuda_standalone PRIVATE ${PROJECT_SOURCE_DIR}/../libivhd_cuda/include)
target_include_directories(ivhd_cuda_standalone PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)
target_include_directories(ivhd_cuda_standalone PRIVATE ${CUDA_INCLUDE_DIRS}/)

target_link_directories(ivhd_cuda_standalone PRIVATE ${PROJECT_SOURCE_DIR}/../build/libivhd/)
target_link_directories(ivhd_cuda_standalone PRIVATE ${PROJECT_SOURCE_DIR}/../build/libivhd_cuda/)

target_link_libraries(ivhd_cuda_standalone cuda libivhd libivhd_cuda)
