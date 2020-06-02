cmake_minimum_required(VERSION 3.15)
project(libviskit_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        core/LoggerTest.cpp
        embed/CasterTest.cpp
        graph/GraphTest.cpp
        graph/KDTreeTest.cpp
        ivhd/InteractiveVisualizationBuilderTest.cpp
        particles/ParticleData.cpp
        threading/ThreadPoolTest.cpp
        TestUtils.h)


add_subdirectory(${PROJECT_SOURCE_DIR}/googletest/)

# include ivhd and ivhd_cuda
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libviskit/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)

# include and link google test
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../googletest/googletest/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../googletest/googlemock/include)

target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries/faiss)

target_link_libraries(${PROJECT_NAME} gtest gmock libviskit)