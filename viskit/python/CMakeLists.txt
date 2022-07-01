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
        bindings/PyParserBinding.h
        bindings/PyParticleSystemBinding.h
        bindings/PyDataPointBinding.h
        bindings/PyGraphBinding.h
        bindings/PyGraphGeneratorBinding.h
        bindings/PyFacadeCasterBinding.h
        )

set(PYVISKIT_SRC
        bindings/PyCasterBinding.cpp
        bindings/PyInteractiveVisualizationBinding.cpp
        bindings/PyResourceFactoryBinding.cpp
        bindings/PyTransformerBinding.cpp
        bindings/PyParserBinding.cpp
        module_binder.cpp
        bindings/PyParticleSystemBinding.cpp
        bindings/PyDataPointBinding.cpp
        bindings/PyGraphBinding.cpp
        bindings/PyGraphGeneratorBinding.cpp
        bindings/PyFacadeCasterBinding.cpp
        )

set(CMAKE_CXX_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden" )

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

pybind11_add_module(pyviskit_bindings ${PYVISKIT_SRC})

if(PROJECT_IS_TOP_LEVEL)
    set(PYVISKIT_HEADERS ${PYVISKIT_HEADERS})
    target_include_directories(pyviskit_bindings PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>)
    target_link_directories(pyviskit_bindings PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-build-release/viskit>)
else()
    set(PYVISKIT_HEADERS ${PYVISKIT_HEADERS} PARENT_SCOPE)
endif()

target_link_libraries(pyviskit_bindings PRIVATE viskit)
target_compile_definitions(pyviskit_bindings PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})