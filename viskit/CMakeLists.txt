set(VISKIT_HEADERS
    core/Core.h
    core/Logger.h
    core/System.h
    embed/cast/ivhd/CasterAdadelta.h
    embed/cast/ivhd/CasterAdam.h
    embed/cast/ivhd/CasterForceDirected.h
    embed/cast/ivhd/CasterIVHD.h
    embed/cast/ivhd/CasterMDS.h
    embed/cast/ivhd/CasterMomentum.h
    embed/cast/ivhd/CasterNesterov.h
    embed/cast/ivhd/CasterSGD.h
    embed/cast/tsne/tsne.h
    embed/cast/tsne/sptree.h
    embed/cast/tsne/vptree.h.h
    embed/cast/Caster.h
    embed/cast/CasterRandom.h
    embed/cast/CasterLargeVis.h
    embed/cast/CasterTSNE.h
    embed/cast/ICaster.h
    embed/cast/umap/CasterUMAP.h
    embed/cast/umap/Umap.h
    embed/cast/umap/combine_neighbor_sets.h
    embed/cast/umap/find_ab.h
    embed/cast/umap/neighbor_similarities.h
    embed/cast/umap/NeighborList.h
    embed/cast/umap/optimize_layout.h
    embed/cast/umap/spectral_init.h
    facade/FacadeCaster.h
    facade/FacadeCasterAdadelta.h
    facade/FacadeCasterAdam.h
    facade/FacadeCasterForceDirected.h
    facade/FacadeCasterMomentum.h
    facade/FacadeCasterNesterov.h
    facade/FacadeCasterRandom.h
    facade/FacadeCasterTSNE.h
    facade/FacadeCasterSGD.h
    facade/FacadeCasterLargeVis.h
    facade/FacadeCasterUMAP.h
    facade/FacadeGraph.h
    facade/FacadeGraphGenerator.h
    facade/FacadeGraphGeneratorBruteForce.h
    facade/FacadeGraphGeneratorKDTree.h
    facade/FacadeGraphGeneratorRandom.h
    facade/FacadeGraphGeneratorReverse.h
    facade/FacadeGraphGeneratorFaiss.h
    facade/FacadeInteractiveVisualization.h
    facade/FacadeMath.h
    facade/FacadeParser.h
    facade/FacadeParserCSV.h
    facade/FacadeParticleSystem.h
    facade/FacadeResourceFactory.h
    graph/generate/BoundedPQueue.h
    graph/generate/BruteForce.h
    graph/generate/GraphGenerator.h
    graph/generate/IGraphGenerator.h
    graph/generate/KDTree.h
    gpu/graph/generate/Faiss.h
    graph/generate/Random.h
    graph/generate/Reverse.h
    graph/Graph.h
    viskit/ICaster.h
    viskit/IGraph.h
    viskit/IGraphGenerator.h
    viskit/IInteractiveVisualization.h
    viskit/InteractiveVisualizationBuilder.h
    viskit/IParser.h
    viskit/IParticleSystem.h
    viskit/IReducer.h
    viskit/ResourceCollection.h
    viskit/ResourceCollection.inl
    viskit/IResourceFactory.h
    viskit/ISetting.h
    viskit/ITransformer.h
    viskit/LogLevel.h
    viskit/Math.h
    viskit/SettingType.h
    viskit/Structures.h
    viskit/IMetric.h
    viskit/DataPoint.h
    facade/metrics/FacadeKnnMetric.h
    math/glm_adapter.h
    math/IvhdMath.h
    parse/Parser.h
    parse/ParserCSV.h
    particles/ParticleData.h
    particles/ParticleSystem.h
    threading/ThreadPool.h
    utils/Math.h
    utils/RandomColor.h
    utils/TimeProfiler.h
)

set(VISKIT_SRC
    core/Core.cpp
    core/Logger.cpp
    core/System.cpp
    embed/cast/ivhd/CasterAdadelta.cpp
    embed/cast/ivhd/CasterAdam.cpp
    embed/cast/ivhd/CasterForceDirected.cpp
    embed/cast/ivhd/CasterIVHD.cpp
    embed/cast/ivhd/CasterMomentum.cpp
    embed/cast/ivhd/CasterNesterov.cpp
    embed/cast/ivhd/CasterSGD.cpp
    embed/cast/Caster.cpp
    embed/cast/CasterRandom.cpp
    embed/cast/CasterTSNE.cpp
    embed/cast/CasterLargeVis.cpp
    embed/cast/umap/CasterUMAP.cpp
    embed/cast/tsne/tsne.cpp
    embed/cast/tsne/sptree.cpp
    facade/FacadeCaster.cpp
    facade/FacadeCasterAdadelta.cpp
    facade/FacadeCasterAdam.cpp
    facade/FacadeCasterForceDirected.cpp
    facade/FacadeCasterMomentum.cpp
    facade/FacadeCasterNesterov.cpp
    facade/FacadeCasterRandom.cpp
    facade/FacadeCasterTSNE.cpp
    facade/FacadeCasterSGD.cpp
    facade/FacadeCasterLargeVis.cpp
    facade/FacadeCasterUMAP.cpp
    facade/FacadeGraph.cpp
    facade/FacadeGraphGenerator.cpp
    facade/FacadeGraphGeneratorBruteForce.cpp
    facade/FacadeGraphGeneratorKDTree.cpp
    facade/FacadeGraphGeneratorRandom.cpp
    facade/FacadeGraphGeneratorReverse.cpp
    facade/FacadeInteractiveVisualization.cpp
    facade/FacadeParser.cpp
    facade/FacadeParserCSV.cpp
    facade/FacadeParticleSystem.cpp
    facade/FacadeResourceFactory.cpp
    graph/generate/BoundedPQueue.cpp
    graph/generate/BruteForce.cpp
    graph/generate/GraphGenerator.cpp
    graph/generate/KDTree.cpp
    graph/generate/Random.cpp
    graph/generate/Reverse.cpp
    graph/Graph.cpp
    facade/metrics/FacadeKnnMetric.cpp
    viskit/InteractiveVisualizationBuilder.cpp
    parse/Parser.cpp
    parse/ParserCSV.cpp
    particles/ParticleData.cpp
    particles/ParticleSystem.cpp
    threading/ThreadPool.cpp
    utils/RandomColor.cpp
    utils/TimeProfiler.cpp)

set(VISKIT_HEADERS ${VISKIT_HEADERS} PARENT_SCOPE)

add_library(viskit ${VISKIT_SRC})

target_include_directories(viskit PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    )

set_target_properties(viskit PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

if(WIN32)
    target_compile_definitions(viskit PRIVATE VISKIT_MAIN_LIB)
endif()

target_compile_definitions(viskit PRIVATE FINTEGER=int)

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(viskit PRIVATE GSL::gsl GSL::gslcblas)

find_package(OpenMP REQUIRED)
find_package (Eigen3 3.3 REQUIRED)
target_link_libraries(viskit PRIVATE OpenMP::OpenMP_CXX Eigen3::Eigen)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)

find_package(MKL)
if(MKL_FOUND)
    target_link_libraries(viskit PRIVATE ${MKL_LIBRARIES})
else()
    find_package(BLAS REQUIRED)
    target_link_libraries(viskit PRIVATE ${BLAS_LIBRARIES})

    find_package(LAPACK REQUIRED)
    target_link_libraries(viskit PRIVATE ${LAPACK_LIBRARIES})
endif()

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(viskit ${Boost_LIBRARIES})
endif()

install(TARGETS viskit
        EXPORT viskit-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

foreach(header ${VISKIT_HEADERS})
    get_filename_component(dir ${header} DIRECTORY )
    install(FILES ${header}
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/viskit/${dir}
            )
endforeach()

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/cmake/viskit-config-version.cmake"
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_file(${PROJECT_SOURCE_DIR}/cmake/viskit-config.cmake.in
        ${PROJECT_BINARY_DIR}/cmake/viskit-config.cmake
        COPYONLY
        )

install(FILES ${PROJECT_BINARY_DIR}/cmake/viskit-config.cmake
        ${PROJECT_BINARY_DIR}/cmake/viskit-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/viskit
        )

install(EXPORT viskit-targets
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/viskit
        )
