project(libivhd CXX)

################################################################################
# Source groups
################################################################################
set(Header_Files__core
    "include/core/Core.h"
    "include/core/Logger.h"
    "include/core/System.h"
)
source_group("Header Files\\core" FILES ${Header_Files__core})

set(Header_Files__embed__cast
    "include/embed/cast/Caster.h"
    "include/embed/cast/CasterRandom.h"
    "include/embed/cast/ICaster.h"
)
source_group("Header Files\\embed\\cast" FILES ${Header_Files__embed__cast})

set(Header_Files__embed__cast__ivhd
    "include/embed/cast/ivhd/CasterAdadelta.h"
    "include/embed/cast/ivhd/CasterAdam.h"
    "include/embed/cast/ivhd/CasterForceDirected.h"
    "include/embed/cast/ivhd/CasterIVHD.h"
    "include/embed/cast/ivhd/CasterMomentum.h"
    "include/embed/cast/ivhd/CasterNesterov.h"
    "include/embed/cast/ivhd/CasterSGD.h"
)
source_group("Header Files\\embed\\cast\\ivhd" FILES ${Header_Files__embed__cast__ivhd})

set(Header_Files__facade
    "include/facade/FacadeCaster.h"
    "include/facade/FacadeCasterAdadelta.h"
    "include/facade/FacadeCasterAdam.h"
    "include/facade/FacadeCasterForceDirected.h"
    "include/facade/FacadeCasterMomentum.h"
    "include/facade/FacadeCasterNesterov.h"
    "include/facade/FacadeCasterRandom.h"
    "include/facade/FacadeGraph.h"
    "include/facade/FacadeGraphGenerator.h"
    "include/facade/FacadeGraphGeneratorBruteForce.h"
    "include/facade/FacadeGraphGeneratorKDTree.h"
    "include/facade/FacadeInteractiveVisualization.h"
    "include/facade/FacadeMath.h"
    "include/facade/FacadeParser.h"
    "include/facade/FacadeParserCSV.h"
    "include/facade/FacadeParticleSystem.h"
    "include/facade/FacadeResourceCollection.h"
    "include/facade/FacadeResourceFactory.h"
    "include/facade/FacadeTransformer.h"
)
source_group("Header Files\\facade" FILES ${Header_Files__facade})

set(Header_Files__graph
    "include/graph/Graph.h"
)
source_group("Header Files\\graph" FILES ${Header_Files__graph})

set(Header_Files__graph__generate
    "include/graph/generate/BoundedPQueue.h"
    "include/graph/generate/BruteForce.h"
    "include/graph/generate/GraphGenerator.h"
    "include/graph/generate/IGraphGenerator.h"
    "include/graph/generate/KDTree.h"
)
source_group("Header Files\\graph\\generate" FILES ${Header_Files__graph__generate})

set(Header_Files__ivhd
    "include/ivhd/ICaster.h"
    "include/ivhd/ICasterDpd.h"
    "include/ivhd/IClusterer.h"
    "include/ivhd/IGraph.h"
    "include/ivhd/IGraphGenerator.h"
    "include/ivhd/IInteractiveVisualization.h"
    "include/ivhd/InteractiveVisualizationBuilder.h"
    "include/ivhd/IParser.h"
    "include/ivhd/IParticleSystem.h"
    "include/ivhd/IReducer.h"
    "include/ivhd/IResourceCollection.h"
    "include/ivhd/IResourceFactory.h"
    "include/ivhd/ISetting.h"
    "include/ivhd/ITransformer.h"
    "include/ivhd/LogLevel.h"
    "include/ivhd/Math.h"
    "include/ivhd/SettingType.h"
    "include/ivhd/Structures.h"
)
source_group("Header Files\\ivhd" FILES ${Header_Files__ivhd})

set(Header_Files__math
    "include/math/glm_adapter.h"
    "include/math/IvhdMath.h"
)
source_group("Header Files\\math" FILES ${Header_Files__math})

set(Header_Files__parse
    "include/parse/Parser.h"
    "include/parse/ParserCSV.h"
)
source_group("Header Files\\parse" FILES ${Header_Files__parse})

set(Header_Files__particles
    "include/particles/ParticleData.h"
    "include/particles/ParticleSystem.h"
)
source_group("Header Files\\particles" FILES ${Header_Files__particles})

set(Header_Files__threading
    "include/threading/ThreadPool.h"
)
source_group("Header Files\\threading" FILES ${Header_Files__threading})

set(Header_Files__utils
    "include/utils/Math.h"
    "include/utils/RandomColor.h"
    "include/utils/TimeProfiler.h"
)
source_group("Header Files\\utils" FILES ${Header_Files__utils})

set(Source_Files__core
    "source/core/Core.cpp"
    "source/core/Logger.cpp"
    "source/core/System.cpp"
)
source_group("Source Files\\core" FILES ${Source_Files__core})

set(Source_Files__embed__cast
    "source/embed/cast/Caster.cpp"
    "source/embed/cast/CasterRandom.cpp"
)
source_group("Source Files\\embed\\cast" FILES ${Source_Files__embed__cast})

set(Source_Files__embed__cast__ivhd
    "source/embed/cast/ivhd/CasterAdadelta.cpp"
    "source/embed/cast/ivhd/CasterAdam.cpp"
    "source/embed/cast/ivhd/CasterForceDirected.cpp"
    "source/embed/cast/ivhd/CasterIVHD.cpp"
    "source/embed/cast/ivhd/CasterMomentum.cpp"
    "source/embed/cast/ivhd/CasterNesterov.cpp"
    "source/embed/cast/ivhd/CasterSGD.cpp"
)
source_group("Source Files\\embed\\cast\\ivhd" FILES ${Source_Files__embed__cast__ivhd})

set(Source_Files__facade
    "source/facade/FacadeCaster.cpp"
    "source/facade/FacadeCasterAdadelta.cpp"
    "source/facade/FacadeCasterAdam.cpp"
    "source/facade/FacadeCasterForceDirected.cpp"
    "source/facade/FacadeCasterMomentum.cpp"
    "source/facade/FacadeCasterNesterov.cpp"
    "source/facade/FacadeCasterRandom.cpp"
    "source/facade/FacadeGraph.cpp"
    "source/facade/FacadeGraphGenerator.cpp"
    "source/facade/FacadeGraphGeneratorBruteForce.cpp"
    "source/facade/FacadeGraphGeneratorKDTree.cpp"
    "source/facade/FacadeInteractiveVisualization.cpp"
    "source/facade/FacadeParser.cpp"
    "source/facade/FacadeParserCSV.cpp"
    "source/facade/FacadeParticleSystem.cpp"
    "source/facade/FacadeResourceFactory.cpp"
)
source_group("Source Files\\facade" FILES ${Source_Files__facade})

set(Source_Files__graph
    "source/graph/Graph.cpp"
)
source_group("Source Files\\graph" FILES ${Source_Files__graph})

set(Source_Files__graph__generate
    "source/graph/generate/BoundedPQueue.cpp"
    "source/graph/generate/BruteForce.cpp"
    "source/graph/generate/GraphGenerator.cpp"
    "source/graph/generate/KDTree.cpp"
)
source_group("Source Files\\graph\\generate" FILES ${Source_Files__graph__generate})

set(Source_Files__ivhd
    "source/ivhd/InteractiveVisualizationBuilder.cpp"
)
source_group("Source Files\\ivhd" FILES ${Source_Files__ivhd})

set(Source_Files__parse
    "source/parse/Parser.cpp"
    "source/parse/ParserCSV.cpp"
)
source_group("Source Files\\parse" FILES ${Source_Files__parse})

set(Source_Files__particles
    "source/particles/ParticleData.cpp"
    "source/particles/ParticleSystem.cpp"
)
source_group("Source Files\\particles" FILES ${Source_Files__particles})

set(Source_Files__threading
    "source/threading/ThreadPool.cpp"
)
source_group("Source Files\\threading" FILES ${Source_Files__threading})

set(Source_Files__utils
    "source/utils/RandomColor.cpp"
    "source/utils/TimeProfiler.cpp"
)
source_group("Source Files\\utils" FILES ${Source_Files__utils})

set(ALL_FILES
    ${Header_Files__core}
    ${Header_Files__embed__cast}
    ${Header_Files__embed__cast__ivhd}
    ${Header_Files__facade}
    ${Header_Files__graph}
    ${Header_Files__graph__generate}
    ${Header_Files__ivhd}
    ${Header_Files__math}
    ${Header_Files__parse}
    ${Header_Files__particles}
    ${Header_Files__threading}
    ${Header_Files__utils}
    ${Source_Files__core}
    ${Source_Files__embed__cast}
    ${Source_Files__embed__cast__ivhd}
    ${Source_Files__facade}
    ${Source_Files__graph}
    ${Source_Files__graph__generate}
    ${Source_Files__ivhd}
    ${Source_Files__parse}
    ${Source_Files__particles}
    ${Source_Files__threading}
    ${Source_Files__utils}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE libivhd)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_LIB;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_LIB;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                ${DEFAULT_CXX_RUNTIME_LIBRARY};
                /Gy
            >
            /permissive-;
            /std:c++17;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                ${DEFAULT_CXX_DEBUG_RUNTIME_LIBRARY}
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                ${DEFAULT_CXX_RUNTIME_LIBRARY};
                /Gy
            >
            /permissive-;
            /std:c++17;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

