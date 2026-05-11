#include "cameraController.h"

CameraController::CameraController(Camera& cam, GLFWWindow& win)
    : camera(cam), window(win), firstMouse(true)
{
    window.setWindowUserPointer(this);

    window.setCursorPosCallback(cursorPosCallback);
    window.setScrollCallback(scrollCallback);
    window.setMouseButtonCallback(mouseButtonCallback);
}

CameraController::~CameraController()
{
    window.setCursorPosCallback(nullptr);
    window.setScrollCallback(nullptr);
    window.setMouseButtonCallback(nullptr);
}

void CameraController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto* controller = static_cast<CameraController*>(glfwGetWindowUserPointer(window));
    if (controller) controller->onMouseButton(button, action);
}

void CameraController::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto* controller = static_cast<CameraController*>(glfwGetWindowUserPointer(window));
    if (controller) controller->onCursorMove(xpos, ypos);
}

void CameraController::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto* controller = static_cast<CameraController*>(glfwGetWindowUserPointer(window));
    if (controller) controller->onScroll(yoffset);
}

void CameraController::onMouseButton(int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        window.getCursorPos(lastMouseX, lastMouseY);
        firstMouse = true;
    }
}

void CameraController::onCursorMove(double xpos, double ypos)
{
    if (window.getMouseButton(GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
        return;

    if (firstMouse)
    {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
        return;
    }

    double xoffset = xpos - lastMouseX;
    double yoffset = lastMouseY - ypos;
    lastMouseX = xpos;
    lastMouseY = ypos;

    camera.rotate(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

void CameraController::onScroll(double yoffset)
{
    camera.zoom(static_cast<float>(-yoffset) * 1.0f);
}