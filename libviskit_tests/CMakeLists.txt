cmake_minimum_required(VERSION 3.15)
project(viskit_tests)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(${PROJECT_NAME}
        core/LoggerTest.cpp
        embed/CasterTest.cpp
        graph/BruteForceTest.cpp
        graph/KDTreeTest.cpp
        graph/ReverseTest.cpp
        ivhd/InteractiveVisualizationBuilderTest.cpp
        threading/ThreadPoolTest.cpp
        TestUtils.h)


add_subdirectory(${PROJECT_SOURCE_DIR}/googletest/)
target_include_directories(${PROJECT_NAME} PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# include viskit and ivhd_cuda
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libviskit/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)

# include and link google test
#target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../googletest/googletest/include)
#target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../googletest/googlemock/include)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries/faiss)

target_link_libraries(${PROJECT_NAME} gtest gtest_main viskit faiss cudart cublas )