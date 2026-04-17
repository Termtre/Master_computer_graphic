#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "vertex.h"

struct line
{
    vertex3f from;
    vertex3f to;

    line(const vertex3f& _from, const vertex3f& _to) :
    from(_from), to(_to)
    {}

    void draw(const glm::vec4& color, float width) const
    {
        glColor4f(color.x, color.y, color.z, color.w);
        glLineWidth(width);
        glBegin(GL_LINES);
            from.draw();
            to.draw();
        glEnd();
    }
};

struct draw_line
{
    static void draw(const line& _line, const glm::vec4& color, float width)
    {
        _line.draw(color, width);
    }
};