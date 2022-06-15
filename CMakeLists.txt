cmake_minimum_required(VERSION 3.20.2)
project(Pseudo3DGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

FILE(GLOB SOURCE CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(Pseudo3DGame ${SOURCE})


target_link_libraries(Pseudo3DGame PRIVATE sfml-graphics sfml-audio)
target_compile_definitions(Pseudo3DGame PRIVATE DATA_DIR="${CMAKE_SOURCE_DIR}/data")
target_compile_features(Pseudo3DGame PRIVATE cxx_std_20)

add_custom_target(release COMMAND Pseudo3DGame)