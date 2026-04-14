#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include "camera.h"

struct column
{
    glm::vec3 center;
    float radius;
    float height;
    glm::vec3 axis;
    glm::vec3 up;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    column(const glm::vec3& _center, float _radius, float _height, const glm::vec3& _axis = {0.f, 1.f, 0.f}) : 
    center(_center), radius(_radius), height(_height), axis(glm::normalize(_axis))
    {
        up = (glm::abs(glm::dot(axis, {0.f, 1.f, 0.f})) > 0.9f) ? 
                glm::vec3{1.f, 0.f, 0.f} : glm::vec3{0.f, 1.f, 0.f};

        tangent = glm::normalize(glm::cross(axis, up));
        bitangent = glm::normalize(glm::cross(axis, tangent));
    }

    void draw(const glm::vec4& color, 
            const glm::vec3& offset = {}) const;

    void draw_contour(const Camera& camera, const glm::vec4& color, 
                      float width_line = 1.f, 
                      const glm::vec3& offset = {}) const;

    void draw_full(const Camera& camera, const glm::vec4& color, 
                   const glm::vec4& color_contour,
                   float width_line = 1.f, 
                   const glm::vec3& offset = {}) const;
};

// struct draw_column
// {
//     static void draw(const column& column, 
//                      const glm::vec4& color,
//                      const glm::vec3& offset)
//     {
//         column.draw(color, offset);
//     }

//     static void draw_contour(const column& column, 
//                              const glm::vec4& color,
//                              float width_line,
//                              const glm::vec3& offset)
//     {
//         column.draw_contour(color, width_line, offset);
//     }

//     static void draw_full(const column& column, 
//                           const glm::vec4& color,
//                           const glm::vec4& color_contour,
//                           float width_line,
//                           const glm::vec3& offset)
//     {
//         column.draw_full(color, color_contour, width_line, offset);
//     }
// };