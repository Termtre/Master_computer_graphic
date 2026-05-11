#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "shaderProgram.h"
#include "shader.h"
#include "buffers.h"
#include "glfwWindow.h"
#include "camera.h"
#include "cameraController.h"
#include "skybox.h"

namespace colors
{
    constexpr glm::vec4 WHITE(1, 1, 1, 1);
};

const std::string vertex_shader_source = "shaders/vertex.glsl";
const std::string fragment_shader_source = "shaders/fragment.glsl";

void frambuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char** argv)
{
    GLFWWindow window;
    
    window.init(4, 3);
    window.createWindow(1000, 800, "Fomichev Dmitriy lab2");

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    window.setFramebufferSizeCallback(frambuffer_size_callback);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    Camera camera
    (
        5.0f,
        0.01f,
        -2.0f, 2.0f,
        -2.0f, 2.0f,
        0.3f, 100.0f
    );
    CameraController cameraControll(camera, window);

    std::shared_ptr<Shader> vertex = std::make_shared<Shader>(GL_VERTEX_SHADER, vertex_shader_source);
    std::shared_ptr<Shader> fragment = std::make_shared<Shader>(GL_FRAGMENT_SHADER, fragment_shader_source);
    
    ShaderProgram program{vertex, fragment};

    std::shared_ptr<Shader> skyVertex = std::make_shared<Shader>(GL_VERTEX_SHADER, "shaders/skybox_vertex.glsl");
    std::shared_ptr<Shader> skyFragment = std::make_shared<Shader>(GL_FRAGMENT_SHADER, "shaders/skybox_fragment.glsl");
    ShaderProgram skyboxProgram{skyVertex, skyFragment};

    Skybox skybox;

    std::vector<std::string> faces = 
    {
        "textures/skybox/top.jpg",
        "textures/skybox/top.jpg",
        "textures/skybox/top.jpg",
        "textures/skybox/top.jpg",
        "textures/skybox/top.jpg",
        "textures/skybox/top.jpg"
    };

    if (!skybox.loadCrossMap("textures/skybox/skybox10.jpg")) 
    {
        std::cerr << "Error: can't load skybox\n";
    }

    std::vector<GLfloat> vertices1 = {
        // позиция     // цвет
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // 0 – красный
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // 1 – зелёный
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // 2 – синий
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // 3 – жёлтый
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,   // первый треугольник
        0, 2, 3    // второй треугольник
    };

    std::vector<VertexAttribute> attributes = {
        {0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0},                         // позиция
        {1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float)}          // цвет
    };

    Buffers squareBuffer;
    squareBuffer.setupBuffers(vertices1, indices, attributes);

    Buffers buffers;

    std::vector<GLfloat> vertices = 
    {
        0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1., 2.0, 3.0
    };

    buffers.setupBuffers(vertices);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    GLint viewLoc = glGetUniformLocation(program.getShaderProgramID(), "view");
    GLint projLoc = glGetUniformLocation(program.getShaderProgramID(), "projection");
    GLint skyViewLoc = glGetUniformLocation(skyboxProgram.getShaderProgramID(), "view");
    GLint skyProjLoc = glGetUniformLocation(skyboxProgram.getShaderProgramID(), "projection");

    float lastFrameTime = 0.0f;

    while(!window.windowShouldClose())
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        window.pollEvents();

        glClearColor(
            colors::WHITE.x, 
            colors::WHITE.y, 
            colors::WHITE.z, 
            colors::WHITE.w
        );

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update(deltaTime);

        glm::mat4 view = camera.getViewMatrix();
        int width, height;
        window.getFramebufferSize(width, height);
        glm::mat4 projection = camera.getProjectionMatrix(width, height);

        glDepthMask(GL_FALSE);
        skyboxProgram.use();
        glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(skyProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
        skybox.draw(view, projection);
        glDepthMask(GL_TRUE);

        program.use();

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(buffers.getVAO());
            // glDrawArrays(GL_POINTS, 0, 1);

            glDrawArrays(GL_LINES, 1, 2);
        glBindVertexArray(0);

        glBindVertexArray(squareBuffer.getVAO());
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        window.swapBuffers();
    }

    return 0;
}

void frambuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}