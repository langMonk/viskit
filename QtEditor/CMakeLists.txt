cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(QtEditor)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    message("You are compiling using WINDOWS OS" ...)
    set(CMAKE_PREFIX_PATH "D://Qt//5.12.1//msvc2017_64")
endif (MSVC)

find_package(Qt5 REQUIRED Widgets Gui Core)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if (UNIX)
    set(CMAKE_CXX_FLAGS -pthread)

    message("You are compiling using UNIX OS" ...)
endif (UNIX)

set(project_ui
        include/MainWindow.ui)

set(project_headers
        include/Camera.h
        include/IRenderer.h
        include/MainWindow.h
        include/OpenGLRenderer.h
        include/particleRenderer.h
        include/RendererFactory.h
        include/Shader.h
        include/ShaderLoader.h
        include/ShaderProgram.h
        include/TextureLoader.h)

set(project_resources
        resources/QtEditor.qrc)

set(project_sources
        source/main.cpp
        source/MainWindow.cpp
        source/OpenGLRenderer.cpp
        source/Shader.cpp
        source/ShaderLoader.cpp
        source/ShaderProgram.cpp
        source/TextureLoader.cpp)

      add_executable(${PROJECT_NAME} ${project_ui} ${project_headers} ${project_sources} ${project_resources})

target_include_directories(QtEditor PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(QtEditor PRIVATE ${PROJECT_SOURCE_DIR}/../libviskit/include/viskit)
target_include_directories(QtEditor PRIVATE ${PROJECT_SOURCE_DIR}/../libraries)
target_include_directories(QtEditor PRIVATE ${PROJECT_SOURCE_DIR}/../libraries/glew/include)

target_link_directories(${PROJECT_NAME} PRIVATE /usr/local/lib)
target_link_directories(${PROJECT_NAME} PRIVATE /cmake-build-release/libviskit/)

target_link_libraries(${PROJECT_NAME} SOIL GLEW GL Qt5::Widgets Qt5::Gui Qt5::Core libviskit faiss )

