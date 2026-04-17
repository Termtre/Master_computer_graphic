#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "vertex.h"

struct cube
{
    float height;
    float width;
    float depth;
    glm::vec3 point;

    cube(const vertex3f& _point, float _width = 1.f, float _height = 1.f, float _depth = 1.f,
        float _width_line = 2.f) :
        point(_point.coord), width(_width), height(_height), depth(_depth)
    {}

    void draw(const glm::vec4& color, 
              const glm::vec3& offset = {}) const;

    void draw_contour(const glm::vec4& color, 
                      float width_line = 1.f, 
                      const glm::vec3& offset = {}) const;

    void draw_full(const glm::vec4& color, 
                   const glm::vec4& color_contour,
                   float width_line = 1.f, 
                   const glm::vec3& offset = {}) const;
};

struct draw_cube
{
    static void draw(const cube& cub, 
                     const glm::vec4& color,
                     const glm::vec3& offset)
    {
        cub.draw(color, offset);
    }

    static void draw_contour(const cube& cub, 
                             const glm::vec4& color,
                             float width_line,
                             const glm::vec3& offset)
    {
        cub.draw_contour(color, width_line, offset);
    }

    static void draw_full(const cube& cub, 
                          const glm::vec4& color,
                          const glm::vec4& color_contour,
                          float width_line,
                          const glm::vec3& offset)
    {
        cub.draw_full(color, color_contour, width_line, offset);
    }
};