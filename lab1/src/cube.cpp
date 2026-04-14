#include "cube.h"

void cube::draw(const glm::vec4& color, const glm::vec3& offset) const
{   
    glm::vec3 p1 = point + offset;
    glm::vec3 p2 = p1 + glm::vec3{width, height, depth};

    glColor4f(color.x, color.y, color.z, color.w);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glBegin(GL_QUADS);
        // Передняя грань
        glNormal3f(0.f, 0.f, 1.f);
        draw_vertex3f::draw({p1.x, p1.y, p1.z}); // левый нижний
        draw_vertex3f::draw({p1.x, p2.y, p1.z}); // левый верхний
        draw_vertex3f::draw({p2.x, p2.y, p1.z}); // правый верхний
        draw_vertex3f::draw({p2.x, p1.y, p1.z}); // правый нижний

        // Задняя грань
        glNormal3f(0.f, 0.f, -1.f);
        draw_vertex3f::draw({p2.x, p1.y, p2.z}); // правый нижний
        draw_vertex3f::draw({p2.x, p2.y, p2.z}); // правый верхний
        draw_vertex3f::draw({p1.x, p2.y, p2.z}); // левый верхний
        draw_vertex3f::draw({p1.x, p1.y, p2.z}); // левый нижний

        // Левая грань
        glNormal3f(-1.f, 0.f, 0.f);
        draw_vertex3f::draw({p1.x, p1.y, p2.z}); // задний нижний
        draw_vertex3f::draw({p1.x, p2.y, p2.z}); // задний верхний
        draw_vertex3f::draw({p1.x, p2.y, p1.z}); // передний верхний
        draw_vertex3f::draw({p1.x, p1.y, p1.z}); // передний нижний

        // Правая грань
        glNormal3f(1.f, 0.f, 0.f);
        draw_vertex3f::draw({p2.x, p1.y, p1.z}); // передний нижний
        draw_vertex3f::draw({p2.x, p2.y, p1.z}); // передний верхний
        draw_vertex3f::draw({p2.x, p2.y, p2.z}); // задний верхний
        draw_vertex3f::draw({p2.x, p1.y, p2.z}); // задний нижний

        // Нижняя грань
        glNormal3f(0.f, -1.f, 0.f);
        draw_vertex3f::draw({p1.x, p1.y, p2.z}); // левый задний
        draw_vertex3f::draw({p1.x, p1.y, p1.z}); // левый передний
        draw_vertex3f::draw({p2.x, p1.y, p1.z}); // правый передний
        draw_vertex3f::draw({p2.x, p1.y, p2.z}); // правый задний

        // Верхняя грань
        glNormal3f(0.f, 1.f, 0.f);
        draw_vertex3f::draw({p1.x, p2.y, p1.z}); // левый передний
        draw_vertex3f::draw({p1.x, p2.y, p2.z}); // левый задний
        draw_vertex3f::draw({p2.x, p2.y, p2.z}); // правый задний
        draw_vertex3f::draw({p2.x, p2.y, p1.z}); // правый передний
    glEnd();
    glDisable(GL_POLYGON_OFFSET_FILL);
}

void cube::draw_contour(const glm::vec4& color, float width_line, const glm::vec3& offset) const
{   
    glm::vec3 p1 = point + offset;
    glm::vec3 p2 = p1 + glm::vec3{width, height, depth};

    glColor4f(color.x, color.y, color.z, color.w);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(width_line);
    glDepthFunc(GL_LEQUAL);
    glBegin(GL_QUADS);
        // Передняя грань
        glNormal3f(0.f, 0.f, 1.f);
        draw_vertex3f::draw({p1.x, p1.y, p1.z}); // левый нижний
        draw_vertex3f::draw({p1.x, p2.y, p1.z}); // левый верхний
        draw_vertex3f::draw({p2.x, p2.y, p1.z}); // правый верхний
        draw_vertex3f::draw({p2.x, p1.y, p1.z}); // правый нижний

        // Задняя грань
        glNormal3f(0.f, 0.f, -1.f);
        draw_vertex3f::draw({p2.x, p1.y, p2.z}); // правый нижний
        draw_vertex3f::draw({p2.x, p2.y, p2.z}); // правый верхний
        draw_vertex3f::draw({p1.x, p2.y, p2.z}); // левый верхний
        draw_vertex3f::draw({p1.x, p1.y, p2.z}); // левый нижний

        // Левая грань
        glNormal3f(-1.f, 0.f, 0.f);
        draw_vertex3f::draw({p1.x, p1.y, p2.z}); // задний нижний
        draw_vertex3f::draw({p1.x, p2.y, p2.z}); // задний верхний
        draw_vertex3f::draw({p1.x, p2.y, p1.z}); // передний верхний
        draw_vertex3f::draw({p1.x, p1.y, p1.z}); // передний нижний

        // Правая грань
        glNormal3f(1.f, 0.f, 0.f);
        draw_vertex3f::draw({p2.x, p1.y, p1.z}); // передний нижний
        draw_vertex3f::draw({p2.x, p2.y, p1.z}); // передний верхний
        draw_vertex3f::draw({p2.x, p2.y, p2.z}); // задний верхний
        draw_vertex3f::draw({p2.x, p1.y, p2.z}); // задний нижний

        // Нижняя грань
        glNormal3f(0.f, -1.f, 0.f);
        draw_vertex3f::draw({p1.x, p1.y, p2.z}); // левый задний
        draw_vertex3f::draw({p1.x, p1.y, p1.z}); // левый передний
        draw_vertex3f::draw({p2.x, p1.y, p1.z}); // правый передний
        draw_vertex3f::draw({p2.x, p1.y, p2.z}); // правый задний

        // Верхняя грань
        glNormal3f(0.f, 1.f, 0.f);
        draw_vertex3f::draw({p1.x, p2.y, p1.z}); // левый передний
        draw_vertex3f::draw({p1.x, p2.y, p2.z}); // левый задний
        draw_vertex3f::draw({p2.x, p2.y, p2.z}); // правый задний
        draw_vertex3f::draw({p2.x, p2.y, p1.z}); // правый передний
    glEnd();
    glDepthFunc(GL_LESS);
}

void cube::draw_full(const glm::vec4& color, const glm::vec4& color_contour, float width_line, const glm::vec3& offset) const
{
    draw(color, offset);
    draw_contour(color_contour, width_line, offset);
}