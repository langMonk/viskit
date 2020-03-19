project(QtEditor CXX)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "shaders/fragmentShader.frag"
    "shaders/vertexShader.vert"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "include/Camera.h"
    "include/IRenderer.h"
    "include/RendererFactory.h"
    "include/Shader.h"
    "include/ShaderLoader.h"
    "include/ShaderProgram.h"
    "include/TextureLoader.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "source/main.cpp"
    "source/MainWindow.cpp"
    "source/OpenGLRenderer.cpp"
    "source/Shader.cpp"
    "source/ShaderLoader.cpp"
    "source/ShaderProgram.cpp"
    "source/TextureLoader.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "$(QtMsBuild)/qt.cmake")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Qt4VSv1.0"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${PROJECT_NAME}"
        TARGET_NAME_RELEASE "${PROJECT_NAME}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${PROJECT_NAME}"
        TARGET_NAME_RELEASE "${PROJECT_NAME}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "$ENV{QTDIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles/$<CONFIG>;"
        "$ENV{QTDIR}/include/QtCore;"
        "$ENV{QTDIR}/include/QtGui;"
        "$ENV{QTDIR}/include/QtANGLE;"
        "$ENV{QTDIR}/include/QtOpenGL;"
        "$ENV{QTDIR}/include/QtWidgets;"
        "$ENV{QTDIR}/include/Qt3DCore;"
        "$ENV{QTDIR}/include/Qt3DAnimation;"
        "$ENV{QTDIR}/include/Qt3DExtras;"
        "$ENV{QTDIR}/include/Qt3DInput;"
        "$ENV{QTDIR}/include/Qt3DLogic;"
        "$ENV{QTDIR}/include/Qt3DRender;"
        "$ENV{QTDIR}/include/Qt3DQuick;"
        "$ENV{QTDIR}/include/Qt3DQuickAnimation;"
        "$ENV{QTDIR}/include/Qt3DQuickExtras;"
        "$ENV{QTDIR}/include/Qt3DQuickInput;"
        "$ENV{QTDIR}/include/Qt3DQuickRender;"
        "$ENV{QTDIR}/include/Qt3DQuickScene2D"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "$ENV{QTDIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles/$<CONFIG>;"
        "$ENV{QTDIR}/include/QtCore;"
        "$ENV{QTDIR}/include/QtGui;"
        "$ENV{QTDIR}/include/QtANGLE;"
        "$ENV{QTDIR}/include/QtOpenGL;"
        "$ENV{QTDIR}/include/QtWidgets;"
        "$ENV{QTDIR}/include/Qt3DCore;"
        "$ENV{QTDIR}/include/Qt3DAnimation;"
        "$ENV{QTDIR}/include/Qt3DExtras;"
        "$ENV{QTDIR}/include/Qt3DInput;"
        "$ENV{QTDIR}/include/Qt3DLogic;"
        "$ENV{QTDIR}/include/Qt3DRender;"
        "$ENV{QTDIR}/include/Qt3DQuick;"
        "$ENV{QTDIR}/include/Qt3DQuickAnimation;"
        "$ENV{QTDIR}/include/Qt3DQuickExtras;"
        "$ENV{QTDIR}/include/Qt3DQuickInput;"
        "$ENV{QTDIR}/include/Qt3DQuickRender;"
        "$ENV{QTDIR}/include/Qt3DQuickScene2D"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Release>:"
            "QT_NO_DEBUG;"
            "NDEBUG"
        ">"
        "UNICODE;"
        "_UNICODE;"
        "WIN32;"
        "_ENABLE_EXTENDED_ALIGNED_STORAGE;"
        "WIN64;"
        "QT_DLL;"
        "QT_CORE_LIB;"
        "QT_GUI_LIB;"
        "QT_OPENGL_LIB;"
        "QT_WIDGETS_LIB;"
        "QT_3DCORE_LIB;"
        "QT_3DANIMATION_LIB;"
        "QT_3DEXTRAS_LIB;"
        "QT_3DINPUT_LIB;"
        "QT_3DLOGIC_LIB;"
        "QT_3DRENDER_LIB;"
        "QT_3DQUICK_LIB;"
        "QT_3DQUICKANIMATION_LIB;"
        "QT_3DQUICKEXTRAS_LIB;"
        "QT_3DQUICKINPUT_LIB;"
        "QT_3DQUICKRENDER_LIB;"
        "QT_3DQUICKSCENE2D_LIB"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Release>:"
            "QT_NO_DEBUG;"
            "NDEBUG"
        ">"
        "UNICODE;"
        "_UNICODE;"
        "WIN32;"
        "_ENABLE_EXTENDED_ALIGNED_STORAGE;"
        "WIN64;"
        "QT_DLL;"
        "QT_CORE_LIB;"
        "QT_GUI_LIB;"
        "QT_OPENGL_LIB;"
        "QT_WIDGETS_LIB;"
        "QT_3DCORE_LIB;"
        "QT_3DANIMATION_LIB;"
        "QT_3DEXTRAS_LIB;"
        "QT_3DINPUT_LIB;"
        "QT_3DLOGIC_LIB;"
        "QT_3DRENDER_LIB;"
        "QT_3DQUICK_LIB;"
        "QT_3DQUICKANIMATION_LIB;"
        "QT_3DQUICKEXTRAS_LIB;"
        "QT_3DQUICKINPUT_LIB;"
        "QT_3DQUICKRENDER_LIB;"
        "QT_3DQUICKSCENE2D_LIB"
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
                /MDd;
                /Zi
            >
            $<$<CONFIG:Release>:
                /MD;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Zc:wchar_t
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /MDd;
                /Zi
            >
            $<$<CONFIG:Release>:
                /MD;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Zc:wchar_t
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /DEBUG
            >
            $<$<CONFIG:Release>:
                /PROFILE
            >
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /DEBUG
            >
            $<$<CONFIG:Release>:
                /PROFILE
            >
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    libivhd
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "qtmaind;"
            "Qt5Cored;"
            "Qt5Guid;"
            "Qt5OpenGLd;"
            "Qt5Widgetsd;"
            "Qt53DCored;"
            "Qt53DAnimationd;"
            "Qt53DExtrasd;"
            "Qt53DInputd;"
            "Qt53DLogicd;"
            "Qt53DRenderd;"
            "Qt53DQuickd;"
            "Qt53DQuickAnimationd;"
            "Qt53DQuickExtrasd;"
            "Qt53DQuickInputd;"
            "Qt53DQuickRenderd;"
            "Qt53DQuickScene2Dd"
        ">"
        "$<$<CONFIG:Release>:"
            "qtmain;"
            "Qt5Core;"
            "Qt5Gui;"
            "Qt5OpenGL;"
            "Qt5Widgets;"
            "Qt53DCore;"
            "Qt53DAnimation;"
            "Qt53DExtras;"
            "Qt53DInput;"
            "Qt53DLogic;"
            "Qt53DRender;"
            "Qt53DQuick;"
            "Qt53DQuickAnimation;"
            "Qt53DQuickExtras;"
            "Qt53DQuickInput;"
            "Qt53DQuickRender;"
            "Qt53DQuickScene2D"
        ">"
        "SOIL2_x64;"
        "libivhd;"
        "glew32;"
        "opengl32;"
        "glu32"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "qtmaind;"
            "Qt5Cored;"
            "Qt5Guid;"
            "Qt5OpenGLd;"
            "Qt5Widgetsd;"
            "Qt53DCored;"
            "Qt53DAnimationd;"
            "Qt53DExtrasd;"
            "Qt53DInputd;"
            "Qt53DLogicd;"
            "Qt53DRenderd;"
            "Qt53DQuickd;"
            "Qt53DQuickAnimationd;"
            "Qt53DQuickExtrasd;"
            "Qt53DQuickInputd;"
            "Qt53DQuickRenderd;"
            "Qt53DQuickScene2Dd"
        ">"
        "$<$<CONFIG:Release>:"
            "qtmain;"
            "Qt5Core;"
            "Qt5Gui;"
            "Qt5OpenGL;"
            "Qt5Widgets;"
            "Qt53DCore;"
            "Qt53DAnimation;"
            "Qt53DExtras;"
            "Qt53DInput;"
            "Qt53DLogic;"
            "Qt53DRender;"
            "Qt53DQuick;"
            "Qt53DQuickAnimation;"
            "Qt53DQuickExtras;"
            "Qt53DQuickInput;"
            "Qt53DQuickRender;"
            "Qt53DQuickScene2D"
        ">"
        "SOIL2_x64;"
        "libivhd;"
        "glew32;"
        "opengl32;"
        "glu32"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{QTDIR}/lib"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{QTDIR}/lib"
    )
endif()



























project(QtEditor CXX)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "shaders/fragmentShader.frag"
    "shaders/vertexShader.vert"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "include/Camera.h"
    "include/IRenderer.h"
    "include/RendererFactory.h"
    "include/Shader.h"
    "include/ShaderLoader.h"
    "include/ShaderProgram.h"
    "include/TextureLoader.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "source/main.cpp"
    "source/MainWindow.cpp"
    "source/OpenGLRenderer.cpp"
    "source/Shader.cpp"
    "source/ShaderLoader.cpp"
    "source/ShaderProgram.cpp"
    "source/TextureLoader.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "$(QtMsBuild)/qt.cmake")

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Qt4VSv1.0"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${PROJECT_NAME}"
        TARGET_NAME_RELEASE "${PROJECT_NAME}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${PROJECT_NAME}"
        TARGET_NAME_RELEASE "${PROJECT_NAME}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/output/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "$ENV{QTDIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles/$<CONFIG>;"
        "$ENV{QTDIR}/include/QtCore;"
        "$ENV{QTDIR}/include/QtGui;"
        "$ENV{QTDIR}/include/QtANGLE;"
        "$ENV{QTDIR}/include/QtOpenGL;"
        "$ENV{QTDIR}/include/QtWidgets;"
        "$ENV{QTDIR}/include/Qt3DCore;"
        "$ENV{QTDIR}/include/Qt3DAnimation;"
        "$ENV{QTDIR}/include/Qt3DExtras;"
        "$ENV{QTDIR}/include/Qt3DInput;"
        "$ENV{QTDIR}/include/Qt3DLogic;"
        "$ENV{QTDIR}/include/Qt3DRender;"
        "$ENV{QTDIR}/include/Qt3DQuick;"
        "$ENV{QTDIR}/include/Qt3DQuickAnimation;"
        "$ENV{QTDIR}/include/Qt3DQuickExtras;"
        "$ENV{QTDIR}/include/Qt3DQuickInput;"
        "$ENV{QTDIR}/include/Qt3DQuickRender;"
        "$ENV{QTDIR}/include/Qt3DQuickScene2D"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles;"
        "${CMAKE_CURRENT_SOURCE_DIR}/.;"
        "$ENV{QTDIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles/$<CONFIG>;"
        "$ENV{QTDIR}/include/QtCore;"
        "$ENV{QTDIR}/include/QtGui;"
        "$ENV{QTDIR}/include/QtANGLE;"
        "$ENV{QTDIR}/include/QtOpenGL;"
        "$ENV{QTDIR}/include/QtWidgets;"
        "$ENV{QTDIR}/include/Qt3DCore;"
        "$ENV{QTDIR}/include/Qt3DAnimation;"
        "$ENV{QTDIR}/include/Qt3DExtras;"
        "$ENV{QTDIR}/include/Qt3DInput;"
        "$ENV{QTDIR}/include/Qt3DLogic;"
        "$ENV{QTDIR}/include/Qt3DRender;"
        "$ENV{QTDIR}/include/Qt3DQuick;"
        "$ENV{QTDIR}/include/Qt3DQuickAnimation;"
        "$ENV{QTDIR}/include/Qt3DQuickExtras;"
        "$ENV{QTDIR}/include/Qt3DQuickInput;"
        "$ENV{QTDIR}/include/Qt3DQuickRender;"
        "$ENV{QTDIR}/include/Qt3DQuickScene2D"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Release>:"
            "QT_NO_DEBUG;"
            "NDEBUG"
        ">"
        "UNICODE;"
        "_UNICODE;"
        "WIN32;"
        "_ENABLE_EXTENDED_ALIGNED_STORAGE;"
        "WIN64;"
        "QT_DLL;"
        "QT_CORE_LIB;"
        "QT_GUI_LIB;"
        "QT_OPENGL_LIB;"
        "QT_WIDGETS_LIB;"
        "QT_3DCORE_LIB;"
        "QT_3DANIMATION_LIB;"
        "QT_3DEXTRAS_LIB;"
        "QT_3DINPUT_LIB;"
        "QT_3DLOGIC_LIB;"
        "QT_3DRENDER_LIB;"
        "QT_3DQUICK_LIB;"
        "QT_3DQUICKANIMATION_LIB;"
        "QT_3DQUICKEXTRAS_LIB;"
        "QT_3DQUICKINPUT_LIB;"
        "QT_3DQUICKRENDER_LIB;"
        "QT_3DQUICKSCENE2D_LIB"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Release>:"
            "QT_NO_DEBUG;"
            "NDEBUG"
        ">"
        "UNICODE;"
        "_UNICODE;"
        "WIN32;"
        "_ENABLE_EXTENDED_ALIGNED_STORAGE;"
        "WIN64;"
        "QT_DLL;"
        "QT_CORE_LIB;"
        "QT_GUI_LIB;"
        "QT_OPENGL_LIB;"
        "QT_WIDGETS_LIB;"
        "QT_3DCORE_LIB;"
        "QT_3DANIMATION_LIB;"
        "QT_3DEXTRAS_LIB;"
        "QT_3DINPUT_LIB;"
        "QT_3DLOGIC_LIB;"
        "QT_3DRENDER_LIB;"
        "QT_3DQUICK_LIB;"
        "QT_3DQUICKANIMATION_LIB;"
        "QT_3DQUICKEXTRAS_LIB;"
        "QT_3DQUICKINPUT_LIB;"
        "QT_3DQUICKRENDER_LIB;"
        "QT_3DQUICKSCENE2D_LIB"
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
                /MDd;
                /Zi
            >
            $<$<CONFIG:Release>:
                /MD;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Zc:wchar_t
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /MDd;
                /Zi
            >
            $<$<CONFIG:Release>:
                /MD;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Zc:wchar_t
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /DEBUG
            >
            $<$<CONFIG:Release>:
                /PROFILE
            >
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /DEBUG
            >
            $<$<CONFIG:Release>:
                /PROFILE
            >
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    libivhd
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "qtmaind;"
            "Qt5Cored;"
            "Qt5Guid;"
            "Qt5OpenGLd;"
            "Qt5Widgetsd;"
            "Qt53DCored;"
            "Qt53DAnimationd;"
            "Qt53DExtrasd;"
            "Qt53DInputd;"
            "Qt53DLogicd;"
            "Qt53DRenderd;"
            "Qt53DQuickd;"
            "Qt53DQuickAnimationd;"
            "Qt53DQuickExtrasd;"
            "Qt53DQuickInputd;"
            "Qt53DQuickRenderd;"
            "Qt53DQuickScene2Dd"
        ">"
        "$<$<CONFIG:Release>:"
            "qtmain;"
            "Qt5Core;"
            "Qt5Gui;"
            "Qt5OpenGL;"
            "Qt5Widgets;"
            "Qt53DCore;"
            "Qt53DAnimation;"
            "Qt53DExtras;"
            "Qt53DInput;"
            "Qt53DLogic;"
            "Qt53DRender;"
            "Qt53DQuick;"
            "Qt53DQuickAnimation;"
            "Qt53DQuickExtras;"
            "Qt53DQuickInput;"
            "Qt53DQuickRender;"
            "Qt53DQuickScene2D"
        ">"
        "SOIL2_x64;"
        "libivhd;"
        "glew32;"
        "opengl32;"
        "glu32"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "qtmaind;"
            "Qt5Cored;"
            "Qt5Guid;"
            "Qt5OpenGLd;"
            "Qt5Widgetsd;"
            "Qt53DCored;"
            "Qt53DAnimationd;"
            "Qt53DExtrasd;"
            "Qt53DInputd;"
            "Qt53DLogicd;"
            "Qt53DRenderd;"
            "Qt53DQuickd;"
            "Qt53DQuickAnimationd;"
            "Qt53DQuickExtrasd;"
            "Qt53DQuickInputd;"
            "Qt53DQuickRenderd;"
            "Qt53DQuickScene2Dd"
        ">"
        "$<$<CONFIG:Release>:"
            "qtmain;"
            "Qt5Core;"
            "Qt5Gui;"
            "Qt5OpenGL;"
            "Qt5Widgets;"
            "Qt53DCore;"
            "Qt53DAnimation;"
            "Qt53DExtras;"
            "Qt53DInput;"
            "Qt53DLogic;"
            "Qt53DRender;"
            "Qt53DQuick;"
            "Qt53DQuickAnimation;"
            "Qt53DQuickExtras;"
            "Qt53DQuickInput;"
            "Qt53DQuickRender;"
            "Qt53DQuickScene2D"
        ">"
        "SOIL2_x64;"
        "libivhd;"
        "glew32;"
        "opengl32;"
        "glu32"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{QTDIR}/lib"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{QTDIR}/lib"
    )
endif()

