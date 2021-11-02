add_executable(viskit_offline viskit_offline.cpp)
target_link_libraries(viskit_offline PRIVATE viskit)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(viskit_offline ${Boost_LIBRARIES})
endif()

