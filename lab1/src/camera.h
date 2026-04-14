#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <GL/glu.h>
#include <numbers>
#include <print>

class Camera
{
    glm::vec3 position;
    glm::vec3 target = {0.f, 0.f, 0.f};
    glm::vec3 up = {0.f, 1.f, 0.f};

    float distance;
    float pitch;
    float yaw;
    float sensitivity;

    float left, right;
    float bottom, top;
    float zNear, zFar;

    float minDistance;
    float maxDistance;

    void updateCameraPosition();

    public:
    Camera(
        float _distance = 300.f, float _sensitivity = 0.01f,
        float _left = -300.f, float _right = 300.f,
        float _bottom = -300.f, float _top = 300.f,
        float _zNear = 0.3f, float _zFar = 1000.f) :
        distance(_distance), sensitivity(_sensitivity), 
        pitch(0.f), yaw(0.f),
        left(_left), right(_right),
        bottom(_bottom), top(_top),
        zNear(_zNear), zFar(_zFar)
    {
        minDistance = distance / 2.f;
        maxDistance = distance * 2.f;

        updateCameraPosition();
    }
    
    void rotate(float delta_X, float delta_Y);

    void applyView() const;

    void applyProjection(int width, int height);

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
        distance += change;
        distance = glm::clamp(distance, minDistance, maxDistance);

        std::println("distance = {}, minDistance = {}, maxDistance = {}", distance, minDistance, maxDistance);

        updateCameraPosition();
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