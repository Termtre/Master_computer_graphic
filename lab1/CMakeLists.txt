cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab1)

set(glm_DIR "~/3rds/glm/share/glm")
set(GLM_INCLUDE_DIR "~/3rds/glm/include")

add_subdirectory(src)

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLU REQUIRED glu)
pkg_check_modules(FreeGLUT REQUIRED glut)

add_executable(lab1 main.cpp)

target_link_libraries(camera PUBLIC
    OpenGL::GL 
    glm::glm
    ${GLU_LIBRARIES}
)

target_link_libraries(primitives PUBLIC
    OpenGL::GL 
    glm::glm 
)

target_link_libraries(lab1 PRIVATE
    ~/3rds/freeglut/lib/libglut.so
    primitives
    camera
)

target_compile_options(camera PUBLIC
    ${GLU_CFLAGS_OTHER})

target_compile_options(lab1 PRIVATE
    ${FreeGLUT_CFLAGS_OTHER})

target_include_directories(lab1 PRIVATE 
    ${PROJECT_SOURCE_DIR}/src
    ${GLU_INCLUDE_DIRS}
    ${FreeGLUT_INCLUDE_DIRS})