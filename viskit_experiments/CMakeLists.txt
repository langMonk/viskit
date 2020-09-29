cmake_minimum_required(VERSION 3.15)
project(viskit_experiments)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        ivhd_rkNN.cpp)

# include viskit and ivhd_cuda
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libviskit/include/viskit)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries/faiss)

target_link_libraries(${PROJECT_NAME} libviskit faiss )