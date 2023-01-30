cmake_minimum_required(VERSION 3.20.2)
project(Pseudo3DGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

FILE(GLOB SOURCE CONFIGURE_DEPENDS src/main.cpp
        src/Core/Entities/World.cpp
        src/Core/Entities/World.h
        src/Core/Entities/2DFigures/Object2D.cpp
        src/Core/Entities/2DFigures/Object2D.h
        src/Core/Helper/Vector.cpp src/Core/Helper/Vector.h
        src/Core/Entities/Camera.cpp
        src/Core/Entities/Camera.h
        src/Core/Entities/2DFigures/Cube.cpp
        src/Core/Entities/2DFigures/Cube.h
        src/Core/Entities/2DFigures/Circle.cpp
        src/Core/Entities/2DFigures/Circle.h
        src/Core/Managers/ResourceManager.cpp
        src/Core/Managers/ResourceManager.h
        src/Core/Engine.cpp src/Core/Engine.h
        src/Core/Helper/Holders/Singleton.h
        src/Core/Managers/IManager.h
        src/Managers.h
        src/Core/Entities/Loaders/WorldLoader.cpp
        src/Core/Entities/Loaders/WorldLoader.h
        src/Core/Painter.cpp
        src/Core/Painter.h
        src/Precompiler.cpp
        src/Precompiler.h
        src/Core/Helper/ConfigParser.cpp
        src/Core/Helper/ConfigParser.h)

add_executable(Pseudo3DGame ${SOURCE})

target_link_libraries(Pseudo3DGame PRIVATE sfml-graphics sfml-audio)
target_compile_definitions(Pseudo3DGame PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data")
target_compile_features(Pseudo3DGame PRIVATE cxx_std_20)

add_custom_target(release COMMAND Pseudo3DGame)