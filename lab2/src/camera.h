#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <numbers>
#include <print>

class Camera
{
    glm::vec3 position;
    glm::vec3 target = {0.f, 0.f, 0.f};
    glm::vec3 up = {0.f, 1.f, 0.f};

    float distance;
    float targetDistance;
    float pitch;
    float yaw;
    float sensitivity;
    float smoothSpeed;

    float left, right;
    float bottom, top;
    float zNear, zFar;

    float minDistance;
    float maxDistance;

    float fov;

    void updateCameraPosition();

    public:
    Camera(
        float _distance = 300.f, float _sensitivity = 0.01f,
        float _left = -300.f, float _right = 300.f,
        float _bottom = -300.f, float _top = 300.f,
        float _zNear = 0.3f, float _zFar = 1000.f, float _fov = 45.f) :
        distance(_distance), sensitivity(_sensitivity), 
        pitch(0.f), yaw(0.f),
        left(_left), right(_right),
        bottom(_bottom), top(_top),
        zNear(_zNear), zFar(_zFar), 
        fov(_fov), targetDistance(_distance), smoothSpeed(10.0f)
    {
        minDistance = 1.0f;
        maxDistance = distance * 10.f;

        updateCameraPosition();
    }
    
    void rotate(float delta_X, float delta_Y);

    glm::mat4 getViewMatrix() const;

    glm::mat4 getProjectionMatrix(int width, int height);

    const glm::vec3& getPosition() const { return position; }
    const glm::vec3& getTarget() const { return target; }
    const glm::vec3& getUp() const { return up; }

    void setCameraAngle(float _pitch, float _yaw)
    {
        pitch = _pitch;
        yaw = _yaw;
        updateCameraPosition();
    }

    void zoom(float change)
    {
        targetDistance += change;
        targetDistance = glm::clamp(targetDistance, minDistance, maxDistance);
        std::println("targetDistance = {}", targetDistance);
    }

    void update(float deltaTime)
    {
        float t = 1.0f - exp(-smoothSpeed * deltaTime);
        distance += (targetDistance - distance) * t;

        if (fabs(targetDistance - distance) < 0.01f)
        {
            distance = targetDistance;
        }
        
        updateCameraPosition();
    }

    void setFov(float fov)
    {
        this->fov = glm::clamp(fov, 1.0f, 179.0f); 
    }

    void setOrthoParams(float _left, float _right,
                        float _bottom, float _top,
                        float _zNear, float _zFar)
    {
        left = _left;
        right = _right;
        bottom = _bottom;
        top = _top;
        zNear = _zNear;
        zFar = _zFar;
    }
};