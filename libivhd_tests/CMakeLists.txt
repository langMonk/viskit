cmake_minimum_required(VERSION 3.15)
project(libivhd_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(libivhd_tests
        core/LoggerTest.cpp
        embed/CasterTest.cpp
        graph/GraphTest.cpp
        graph/FaissTest.cpp
        graph/KDTreeTest.cpp
        ivhd/InteractiveVisualizationBuilderTest.cpp
        particles/ParticleData.cpp
        threading/ThreadPoolTest.cpp
        TestUtils.h)

# include ivhd
target_include_directories(libivhd_tests PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(libivhd_tests PRIVATE ${PROJECT_SOURCE_DIR}/../libivhd/include)
target_include_directories(libivhd_tests PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)

# include and link google test
target_include_directories(libivhd_tests PRIVATE ${PROJECT_SOURCE_DIR}/../googletest/googletest/include)
target_include_directories(libivhd_tests PRIVATE ${PROJECT_SOURCE_DIR}/../googletest/googlemock/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/googletest/)

target_link_directories(libivhd_tests PRIVATE ${PROJECT_SOURCE_DIR}/../libraries/faiss)

target_link_libraries(libivhd_tests gtest gmock libivhd)