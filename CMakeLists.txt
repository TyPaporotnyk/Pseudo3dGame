cmake_minimum_required(VERSION 3.20.2)
project(Pseudo3DGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Используем shared libs
set(SFML_STATIC_LIBRARIES OFF)

# Добавляем submodule
add_subdirectory(external/SFML)

# Собираем проект
file(GLOB_RECURSE SOURCE
    src/*.cpp
    src/**/*.cpp
    src/**/*.h
)

add_executable(Pseudo3DGame ${SOURCE})

# Линкуем SFML 2.5
target_link_libraries(Pseudo3DGame PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
target_compile_definitions(Pseudo3DGame PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data")
