cmake_minimum_required(VERSION 3.15)
project(libviskit)

set(CMAKE_CXX_STANDARD 17)

###
### Comment this 2 lines if library should be compiled without CUDA/FAISS
###
add_compile_definitions(USE_CUDA)
set(USE_CUDA TRUE)

set(CUDA_FILES
        include/graph/generate/Faiss.h
        source/graph/generate/Faiss.cpp
        include/facade/FacadeGraphGeneratorFaiss.h
        source/facade/FacadeGraphGeneratorFaiss.cpp
        )

set(HEADER_FILES
        include/core/Core.h
        include/core/Logger.h
        include/core/System.h
        include/embed/cast/ivhd/CasterAdadelta.h
        include/embed/cast/ivhd/CasterAdam.h
        include/embed/cast/ivhd/CasterForceDirected.h
        include/embed/cast/ivhd/CasterIVHD.h
        include/embed/cast/ivhd/CasterMDS.h
        include/embed/cast/ivhd/CasterMomentum.h
        include/embed/cast/ivhd/CasterNesterov.h
        include/embed/cast/ivhd/CasterSGD.h
        include/embed/cast/Caster.h
        include/embed/cast/CasterRandom.h
        include/embed/cast/ICaster.h
        include/facade/FacadeCaster.h
        include/facade/FacadeCasterAdadelta.h
        include/facade/FacadeCasterAdam.h
        include/facade/FacadeCasterForceDirected.h
        include/facade/FacadeCasterMomentum.h
        include/facade/FacadeCasterNesterov.h
        include/facade/FacadeCasterRandom.h
        include/facade/FacadeCasterSGD.h
        include/facade/FacadeGraph.h
        include/facade/FacadeGraphGenerator.h
        include/facade/FacadeGraphGeneratorBruteForce.h
        include/facade/FacadeGraphGeneratorKDTree.h
        include/facade/FacadeGraphGeneratorRandom.h
        include/facade/FacadeInteractiveVisualization.h
        include/facade/FacadeMath.h
        include/facade/FacadeParser.h
        include/facade/FacadeParserCSV.h
        include/facade/FacadeParticleSystem.h
        include/facade/FacadeResourceFactory.h
        include/facade/FacadeTransformer.h
        include/graph/generate/BoundedPQueue.h
        include/graph/generate/BruteForce.h
        include/graph/generate/GraphGenerator.h
        include/graph/generate/IGraphGenerator.h
        include/graph/generate/KDTree.h
        include/graph/generate/Faiss.h
        include/graph/generate/Random.h
        include/graph/generate/Reverse.h
        include/graph/DataPoint.h
        include/graph/Graph.h
        include/graph/IGraph.h
        include/viskit/ICaster.h
        include/viskit/IClusterer.h
        include/viskit/IGraph.h
        include/viskit/IGraphGenerator.h
        include/viskit/IInteractiveVisualization.h
        include/viskit/InteractiveVisualizationBuilder.h
        include/viskit/IParser.h
        include/viskit/IParticleSystem.h
        include/viskit/IReducer.h
        include/viskit/ResourceCollection.h
        include/viskit/IResourceFactory.h
        include/viskit/ISetting.h
        include/viskit/ITransformer.h
        include/viskit/LogLevel.h
        include/viskit/Math.h
        include/viskit/SettingType.h
        include/viskit/Structures.h
        include/math/glm_adapter.h
        include/math/IvhdMath.h
        include/parse/Parser.h
        include/parse/ParserCSV.h
        include/particles/ParticleData.h
        include/particles/ParticleSystem.h
        include/threading/ThreadPool.h
        include/utils/Math.h
        include/utils/RandomColor.h
        include/utils/TimeProfiler.h
        )

set(SOURCE_FILES
        source/core/Core.cpp
        source/core/Logger.cpp
        source/core/System.cpp
        source/embed/cast/ivhd/CasterAdadelta.cpp
        source/embed/cast/ivhd/CasterAdam.cpp
        source/embed/cast/ivhd/CasterForceDirected.cpp
        source/embed/cast/ivhd/CasterIVHD.cpp
        source/embed/cast/ivhd/CasterMomentum.cpp
        source/embed/cast/ivhd/CasterNesterov.cpp
        source/embed/cast/ivhd/CasterSGD.cpp
        source/embed/cast/Caster.cpp
        source/embed/cast/CasterRandom.cpp
        source/facade/FacadeCaster.cpp
        source/facade/FacadeCasterAdadelta.cpp
        source/facade/FacadeCasterAdam.cpp
        source/facade/FacadeCasterForceDirected.cpp
        source/facade/FacadeCasterMomentum.cpp
        source/facade/FacadeCasterNesterov.cpp
        source/facade/FacadeCasterRandom.cpp
        source/facade/FacadeCasterSGD.cpp
        source/facade/FacadeGraph.cpp
        source/facade/FacadeGraphGenerator.cpp
        source/facade/FacadeGraphGeneratorBruteForce.cpp
        source/facade/FacadeGraphGeneratorKDTree.cpp
        source/facade/FacadeGraphGeneratorRandom.cpp
        source/facade/FacadeInteractiveVisualization.cpp
        source/facade/FacadeParser.cpp
        source/facade/FacadeParserCSV.cpp
        source/facade/FacadeParticleSystem.cpp
        source/facade/FacadeResourceFactory.cpp
        source/graph/generate/BoundedPQueue.cpp
        source/graph/generate/BruteForce.cpp
        source/graph/generate/GraphGenerator.cpp
        source/graph/generate/KDTree.cpp
        source/graph/generate/Faiss.cpp
        source/graph/generate/Random.cpp
        source/graph/generate/Reverse.cpp
        source/graph/DataPoint.cpp
        source/graph/Graph.cpp
        source/viskit/InteractiveVisualizationBuilder.cpp
        source/parse/Parser.cpp
        source/parse/ParserCSV.cpp
        source/particles/ParticleData.cpp
        source/particles/ParticleSystem.cpp
        source/threading/ThreadPool.cpp
        source/utils/RandomColor.cpp
        source/utils/TimeProfiler.cpp
        )

if (USE_CUDA)
    find_package(CUDA 10.2 REQUIRED)
    message("Compilation with CUDA")
else()
    message("Compilation without CUDA")
endif()

add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${CUDA_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/viskit)
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDA_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} pthread)