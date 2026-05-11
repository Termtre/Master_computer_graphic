add_library(camera STATIC 
        camera.cpp
        cameraController.cpp)

target_link_libraries(camera PRIVATE
    glm::glm
)

add_library (skybox STATIC
        skybox.cpp)

target_link_libraries(skybox PRIVATE
    glad::glad
    glm::glm
)

target_include_directories(skybox PRIVATE 
        ${Stb_INCLUDE_DIR}
)
