#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include "camera.h"

class GLFWWindow
{
    private:

    GLFWwindow* window = nullptr;
    std::string title;

    public:

    GLFWWindow() = default;

    ~GLFWWindow()
    {
        if (window)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }

    void init(int CONTEXT_VERSION_MAJOR, int CONTEXT_VERSION_MINOR, bool CORE_OPENGL_PROFILE = true) 
    {
        if (!glfwInit())
        {
            throw std::runtime_error("GLFW wasn't initialized\n");
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT_VERSION_MINOR);
        if (CORE_OPENGL_PROFILE) glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void createWindow(int width, int height, const std::string& title)
    {
        this->title = title;

        this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

        if (this->window == nullptr)
        {
            glfwTerminate();
            throw std::runtime_error("GLFW window wasn't created\n");
        }

        glfwMakeContextCurrent(this->window);
    }

    void setWindowUserPointer(void* camera)
    {
        glfwSetWindowUserPointer(window, camera);
    }

    void setFramebufferSizeCallback(void (*frambuffer_size_callback)(GLFWwindow *window, int width, int height))
    {
        glfwSetFramebufferSizeCallback(this->window, frambuffer_size_callback);
    }

    void getFramebufferSize(int& width, int& height)
    {
        glfwGetFramebufferSize(window, &width, &height);
    }

    bool windowShouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void pollEvents()
    {
        glfwPollEvents();
    }

    void swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void setInputMode(int mode, int value)
    {
        glfwSetInputMode(window, mode, value);
    }

    void setCursorPosCallback(void (*mouse_callback)(GLFWwindow* window, double xpos, double ypos))
    {
        glfwSetCursorPosCallback(window, mouse_callback);
    }

    void setScrollCallback(void (*scroll_callback)(GLFWwindow* window, double xoffset, double yoffset))
    {
        glfwSetScrollCallback(window, scroll_callback);
    }

    void setKeyCallback(void (*key_callback)(GLFWwindow* window, int key, int scancode, int action, int mods))
    {
        glfwSetKeyCallback(window, key_callback);
    }

    void setMouseButtonCallback(void (*mouse_button_callback)(GLFWwindow* window, int button, int action, int mods))
    {
        glfwSetMouseButtonCallback(window, mouse_button_callback);
    }

    void getCursorPos(double& xpos, double& ypos)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
    }

    int getMouseButton(int button)
    {
        return glfwGetMouseButton(window, button);
    }
};