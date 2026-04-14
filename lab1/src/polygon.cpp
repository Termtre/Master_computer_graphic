#include "polygon.h"

void polygon::draw(const glm::vec4& color, 
              const glm::vec3& offset) const
{
    if (polygons.size() < 3) return;

    glColor4f(color.x, color.y, color.z, color.w);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);

    for (const auto& v : polygons) 
    {
        auto v1 = v;
        v1.coord += offset;
        v1.draw();
    }
    
    glEnd();
}

void polygon::draw_contour(const glm::vec4& color, 
                    float width_line, 
                    const glm::vec3& offset) const
{
    if (polygons.size() < 3) return;

    glColor4f(color.x, color.y, color.z, color.w);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(width_line);
    glBegin(GL_POLYGON);

    for (const auto& v : polygons) 
    {
        auto v1 = v;
        v1.coord += offset;
        v1.draw();
    }
    
    glEnd();
}

void polygon::draw_full(const glm::vec4& color, 
                const glm::vec4& color_contour,
                float width_line, 
                const glm::vec3& offset) const
{
    draw(color, offset);
    draw_contour(color_contour, width_line, offset);
}