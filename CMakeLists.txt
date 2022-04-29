cmake_minimum_required(VERSION 3.20)
project(Pseudo3DGame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Pseudo3DGame src/main.cpp src/World.cpp src/World.h src/2DFigures/Object2D.cpp src/2DFigures/Object2D.h src/IDrawble.h src/Vector.cpp src/Vector.h src/Camera.cpp src/Camera.h src/2DFigures/Cube.cpp src/2DFigures/Cube.h src/2DFigures/Circle.cpp src/2DFigures/Circle.h src/ResourceManager.cpp src/ResourceManager.h)

if(${APPLE})
    include_directories(/usr/local/include)
else()
    set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

target_link_libraries(Pseudo3DGame PRIVATE sfml-graphics sfml-audio)
target_compile_definitions(Pseudo3DGame PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data")
target_compile_features(Pseudo3DGame PRIVATE cxx_std_20)

add_custom_target(release COMMAND Pseudo3DGame)