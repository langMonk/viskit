cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(pyviskit
        VERSION 0.0.1
        DESCRIPTION "A python bindings for viskit."
        HOMEPAGE_URL "https://gitlab.com/bminch/viskit"
        LANGUAGES CXX)

set(PYVISKIT_HEADERS
        bindings/PyCasterBinding.h
        bindings/PyInteractiveVisualizationBinding.h
        bindings/PyResourceFactoryBinding.h
        bindings/PyTransformerBinding.h
        bindings/PyStructuresBinding.h
        )

set(PYVISKIT_SRC
        bindings/PyCasterBinding.cpp
        bindings/PyInteractiveVisualizationBinding.cpp
        bindings/PyResourceFactoryBinding.cpp
        bindings/PyTransformerBinding.cpp
        module_binder.cpp
        )

set(CMAKE_CXX_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden" )

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

pybind11_add_module(pyviskit ${PYVISKIT_SRC})

if(PROJECT_IS_TOP_LEVEL)
    set(PYVISKIT_HEADERS ${PYVISKIT_HEADERS})
    target_include_directories(pyviskit PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>)
    target_link_directories(pyviskit PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-build-release/viskit>)
else()
    set(PYVISKIT_HEADERS ${PYVISKIT_HEADERS} PARENT_SCOPE)
endif()

target_link_libraries(pyviskit PRIVATE viskit)
target_compile_definitions(pyviskit PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})