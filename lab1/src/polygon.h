#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <list>
#include "vertex.h"

struct polygon
{
    std::list<vertex3f> polygons;

    polygon() = default;

    polygon(std::initializer_list<vertex3f> list) : polygons(list)
    {}

    void append(const vertex3f& vert)
    {
        polygons.push_back(vert);
    }

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

struct draw_polygon
{
    static void draw(const polygon& polygon, 
                     const glm::vec4& color,
                     const glm::vec3& offset)
    {
        polygon.draw(color, offset);
    }

    static void draw_contour(const polygon& polygon, 
                             const glm::vec4& color,
                             float width_line,
                             const glm::vec3& offset)
    {
        polygon.draw_contour(color, width_line, offset);
    }

    static void draw_full(const polygon& polygon, 
                          const glm::vec4& color,
                          const glm::vec4& color_contour,
                          float width_line,
                          const glm::vec3& offset)
    {
        polygon.draw_full(color, color_contour, width_line, offset);
    }
};