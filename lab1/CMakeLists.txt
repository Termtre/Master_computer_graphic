cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab1)

find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_subdirectory(src)

add_executable(lab1 main.cpp)

target_link_libraries(lab1 PRIVATE
    GLUT::GLUT
    primitives
    camera
)

target_include_directories(lab1 PRIVATE ${PROJECT_SOURCE_DIR}/src)
