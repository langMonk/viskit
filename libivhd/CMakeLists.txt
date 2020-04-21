cmake_minimum_required(VERSION 3.15)
project(libivhd CUDA)

find_package(CUDA REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_library(libivhd
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
        include/facade/FacadeGraphGeneratorFaiss.h
        include/facade/FacadeGraphGeneratorKDTree.h
        include/facade/FacadeInteractiveVisualization.h
        include/facade/FacadeMath.h
        include/facade/FacadeParser.h
        include/facade/FacadeParserCSV.h
        include/facade/FacadeParticleSystem.h
        include/facade/FacadeResourceCollection.h
        include/facade/FacadeResourceFactory.h
        include/facade/FacadeTransformer.h
        include/graph/generate/BoundedPQueue.h
        include/graph/generate/BruteForce.h
        include/graph/generate/GraphGenerator.h
        include/graph/generate/IGraphGenerator.h
        include/graph/generate/KDTree.h
        include/graph/generate/Faiss.h
        include/graph/DataPoint.h
        include/graph/Graph.h
        include/graph/IGraph.h
        include/ivhd/ICaster.h
        include/ivhd/ICasterDpd.h
        include/ivhd/IClusterer.h
        include/ivhd/IGraph.h
        include/ivhd/IGraphGenerator.h
        include/ivhd/IInteractiveVisualization.h
        include/ivhd/InteractiveVisualizationBuilder.h
        include/ivhd/IParser.h
        include/ivhd/IParticleSystem.h
        include/ivhd/IReducer.h
        include/ivhd/IResourceCollection.h
        include/ivhd/IResourceFactory.h
        include/ivhd/ISetting.h
        include/ivhd/ITransformer.h
        include/ivhd/LogLevel.h
        include/ivhd/Math.h
        include/ivhd/SettingType.h
        include/ivhd/Structures.h
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
        source/facade/FacadeGraphGeneratorFaiss.cpp
        source/facade/FacadeGraphGeneratorKDTree.cpp
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
        source/graph/DataPoint.cpp
        source/graph/Graph.cpp
        source/ivhd/InteractiveVisualizationBuilder.cpp
        source/parse/Parser.cpp
        source/parse/ParserCSV.cpp
        source/particles/ParticleData.cpp
        source/particles/ParticleSystem.cpp
        source/threading/ThreadPool.cpp
        source/utils/RandomColor.cpp
        source/utils/TimeProfiler.cpp)

target_include_directories(libivhd PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)
target_include_directories(libivhd PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(libivhd PRIVATE ${CUDA_INCLUDE_DIRS})

target_link_libraries( libivhd pthread faiss )