#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>

struct vertex3f
{
    glm::vec3 coord;

    vertex3f() = default;

    vertex3f(float x, float y, float z = 0.f) : coord(x, y, z)
    {}

    vertex3f(const glm::vec3& vec) : coord(vec)
    {}

    void draw(const glm::vec4& color) const
    {
        glColor4f(color.x, color.y, color.z, color.w);
        glVertex3f(coord.x, coord.y, coord.z);
    }

    void draw() const
    {
        glVertex3f(coord.x, coord.y, coord.z);
    }
};

struct draw_vertex3f
{
    static void draw(const vertex3f& point)
    {
        point.draw();
    }

    static void draw(const vertex3f& point, const glm::vec4& color)
    {
        point.draw(color);
    }
};