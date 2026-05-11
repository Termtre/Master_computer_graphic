#include "camera.h"
#include <glm/gtc/quaternion.hpp>

void Camera::updateCameraPosition()
{
    glm::quat yawQuat = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
    glm::quat pitchQuat = glm::angleAxis(pitch, glm::vec3(1, 0, 0));

    glm::quat rotation = yawQuat * pitchQuat;

    glm::vec3 forward(0.0f, 0.0f, -1.0f);

    glm::vec3 rotatedForward = rotation * forward;

    position = target + rotatedForward * distance;

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    up = rotation * worldUp;
}

void Camera::rotate(float delta_X, float delta_Y)
{
    yaw += delta_X * sensitivity;
    pitch += delta_Y * sensitivity;

    updateCameraPosition();
}

glm::mat4 Camera::getViewMatrix() const
{   
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix(int width, int height)
{
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    
    // float halfHeight = (top - bottom) * 0.5f;
    // float halfWidth = halfHeight * aspect;
    // return glm::ortho(-halfWidth, halfWidth, bottom, top, zNear, zFar);

    return glm::perspective(glm::radians(fov), aspect, zNear, zFar);
}