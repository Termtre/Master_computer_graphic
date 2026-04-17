add_library(primitives STATIC 
        cube.cpp
        polygon.cpp
        column.cpp)

add_library(camera STATIC 
        camera.cpp)

target_link_libraries(camera PUBLIC
    OpenGL::GL 
    glm::glm
    OpenGL::GLU
)

target_link_libraries(primitives PUBLIC
    OpenGL::GL 
    glm::glm 
)
