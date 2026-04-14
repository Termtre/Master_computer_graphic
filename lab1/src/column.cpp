#include "column.h"
#include <numeric>
#include "vertex.h"
#include "polygon.h"
#include "line.h"

void column::draw(const glm::vec4& color, const glm::vec3& offset) const
{   
    glm::vec3 center1 = center + offset;
    glm::vec3 top_center = center1 + axis * height;
    float segments = 4.f * glm::sqrt(radius);
    float angleStep = 2.f * std::numbers::pi_v<float> / segments;
    
    glColor4f(color.x, color.y, color.z, color.w);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glBegin(GL_QUAD_STRIP);
        for (float i = 0.f; i < segments + 1.f; i += 1.f)
        {
            float angle = i * angleStep;
            glm::vec3 circle_point = radius * (tangent * glm::cos(angle) + bitangent * glm::sin(angle));
            glm::vec3 bottom_point = center1 + circle_point;
            glm::vec3 top_point = center1 + circle_point + axis * height;
            auto normal = glm::normalize(circle_point);
            glNormal3f(normal.x, normal.y, normal.z);
            vertex3f(bottom_point).draw();
            vertex3f(top_point).draw();
        }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(-axis.x, -axis.y, -axis.z);
        vertex3f(center1).draw();
        for (float i = 0.f; i < segments + 1.f; i += 1.f)
        {
            float angle = i * angleStep;
            glm::vec3 circle_point = radius * (tangent * glm::cos(angle) + bitangent * glm::sin(angle));
            glm::vec3 point = center1 + circle_point;
            vertex3f(point).draw();
        }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(axis.x, axis.y, axis.z);
        vertex3f(top_center.x, top_center.y, top_center.z).draw();
        for (float i = 0.f; i < segments + 1.f; i += 1.f)
        {
            float angle = i * angleStep;
            glm::vec3 circle_point = radius * (tangent * glm::cos(angle) + bitangent * glm::sin(angle));
            glm::vec3 point = top_center + circle_point;
            vertex3f(point).draw();
        }
    glEnd();

    glDisable(GL_POLYGON_OFFSET_FILL);
}

void column::draw_contour(const Camera& camera, const glm::vec4& color, float width_line, const glm::vec3& offset) const
{   
    glm::vec3 center1 = center + offset;
    glm::vec3 top_center = center1 + axis * height;
    polygon bottom, top;
    float segments = 4.f * glm::sqrt(radius);
    float angleStep = 2.f * std::numbers::pi_v<float> / segments;
    auto view = glm::normalize(camera.getTarget() - camera.getPosition());

    glm::vec3 inPlane = glm::normalize(glm::cross(axis, view));

    auto dir2D = glm::normalize(glm::vec2{glm::dot(inPlane, tangent), glm::dot(inPlane, bitangent)});

    float angle1 = std::atan2(dir2D.y, dir2D.x);
    float angle2 = angle1 + std::numbers::pi_v<float>;

    glm::vec3 lineDir1 = tangent * glm::cos(angle1) + bitangent * glm::sin(angle1);
    glm::vec3 lineDir2 = tangent * glm::cos(angle2) + bitangent * glm::sin(angle2);

    glm::vec3 bottom1 = radius * lineDir1 + center1;
    glm::vec3 bottom2 = radius * lineDir2 + center1;

    glm::vec3 top1 = radius * lineDir1 + top_center;
    glm::vec3 top2 = radius * lineDir2 + top_center;

    glDepthFunc(GL_LEQUAL);
    draw_line::draw({bottom1, top1}, color, width_line);
    draw_line::draw({bottom2, top2}, color, width_line);

    glColor4f(color.x, color.y, color.z, color.w);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(width_line);
    glDepthFunc(GL_LEQUAL);

    for (float i = 0.f; i < segments + 1.f; i += 1.f)
    {
        float angle = i * angleStep;
        glm::vec3 circle_point = radius * (tangent * glm::cos(angle) + bitangent * glm::sin(angle));
        glm::vec3 point = center1 + circle_point;
        bottom.append(center1 + circle_point);
        top.append(top_center + circle_point);
    }

    bottom.draw_contour(color, width_line);
    top.draw_contour(color, width_line);

    glDepthFunc(GL_LESS);

}

void column::draw_full(const Camera& camera, const glm::vec4& color, const glm::vec4& color_contour, float width_line, const glm::vec3& offset) const
{
    draw(color, offset);
    draw_contour(camera, color_contour, width_line, offset);
}