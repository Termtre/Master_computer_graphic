#pragma once

#include "camera.h"
#include "glfwWindow.h"

class CameraController 
{
private:
    Camera& camera;
    GLFWWindow& window;
    double lastMouseX, lastMouseY;
    bool firstMouse;

public:
    CameraController(Camera& camera, GLFWWindow& window);
    ~CameraController();

    CameraController(const CameraController&) = delete;
    CameraController& operator=(const CameraController&) = delete;

private:

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void onMouseButton(int button, int action);
    void onCursorMove(double xpos, double ypos);
    void onScroll(double yoffset);
};