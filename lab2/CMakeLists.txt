cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab2)

find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory(src)

add_executable(lab2 main.cpp)

add_custom_command(
    TARGET lab2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/shaders"
    "${CMAKE_SOURCE_DIR}/textures"
    "$<TARGET_FILE_DIR:lab2>/shaders"
    "$<TARGET_FILE_DIR:lab2>/textures"
)

target_link_libraries(lab2 PRIVATE
    glfw
    glad::glad
    OpenGL::GL
    glm::glm
    camera
    skybox
)

target_include_directories(lab2 PRIVATE ${PROJECT_SOURCE_DIR}/src)
