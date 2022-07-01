set(VISKIT_TESTS_SRC
    LoggerTest.cpp
    CasterTest.cpp
    BruteForceTest.cpp
    KDTreeTest.cpp
    ReverseTest.cpp
    InteractiveVisualizationBuilderTest.cpp
    ThreadPoolTest.cpp
        GraphTest.cpp)

add_executable(viskit_tests ${VISKIT_TESTS_SRC})

target_link_libraries(viskit_tests PRIVATE viskit pthread)

include(FetchContent)
FetchContent_Declare(googletest
        URL "https://github.com/google/googletest/archive/release-1.11.0.tar.gz")
set(BUILD_GMOCK CACHE BOOL OFF)
set(INSTALL_GTEST CACHE BOOL OFF)
FetchContent_MakeAvailable(googletest)

find_package(OpenMP REQUIRED)
find_package (Eigen3 3.3 REQUIRED)

target_link_libraries(viskit_tests PRIVATE
        OpenMP::OpenMP_CXX
        Eigen3::Eigen
        gtest_main
        )

# Defines `gtest_discover_tests()`.
include(GoogleTest)
gtest_discover_tests(viskit_tests)