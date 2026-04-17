#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include "cube.h"
#include "vertex.h"
#include "camera.h"
#include "polygon.h"
#include "column.h"
#include <clocale>

namespace colorPalette
{
    constexpr auto WHITE = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    constexpr auto BLACK = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    constexpr auto PINKGREY = glm::vec4(0.85f, 0.75f, 0.78f, 1.0f);
    constexpr auto LIGHTGREEN = glm::vec4(0.1f, 0.8f, 0.3f, 1.0f);
    constexpr auto GREY = glm::vec4(0.85f, 0.85f, 0.85f, 1.0f);
    constexpr auto RED = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
};

enum class RenderMode
{
    FULL = 1,
    FILL = 2,    
    CONTOUR = 3
};

RenderMode curMode = RenderMode::FULL;

bool firstMouse = true, mouseCapture = false;
float last_X = 0.f, last_Y = 0.f;
float scene = 350.f;
float width_line = 2.f;
Camera camera(
    scene,
    0.005f,
    -scene, scene,
    -scene, scene,
    0.1f, 1000.f
);

cube background_wall({{-94, -120, 90}, 188, 110, 15});
cube front_step({{-50, -150, -125}, 100, 15, 25});
cube left_top_base({{-135, 110, -110}, 41, 20, 31});
cube roof({{-150, 130, -125}, 300, 20, 250});
cube wall({{-121, -120, -79}, 15, 110, 162});
column left_column({-114.f, -100.f, -94}, 9.f, 210.f);
cube slab({-150, -150, -100}, 300, 30, 225);
cube step({-50, -150, -125}, 100, 15, 25);
cube block({-150, -150, -125}, 100, 30, 25);
polygon slab_contour = {
    {-150, -150, -125},
    {-50, -150, -125},
    {-50, -150, -100},
    {50, -150, -100},
    {50, -150, -125},
    {150, -150, -125},
    {150, -150, 125},
    {-150, -150, 125},
    {-150, -150, -125},
    {-150, -120, -125},
    {-50, -120, -125}, // 1
    {-50, -150, -125}, // 1
    {-50, -120, -125}, // 1
    {-50, -120, -100}, // 2
    {-50, -150, -100}, // 2
    {-50, -120, -100}, // 2
    {50, -120, -100}, // 3
    {50, -150, -100}, // 3
    {50, -120, -100}, // 3
    {50, -120, -125}, // 4
    {50, -150, -125}, // 4
    {50, -120, -125}, // 4
    {150, -120, -125}, // 5
    {150, -150, -125}, // 5
    {150, -120, -125}, // 5
    {150, -120, 125}, // 6
    {150, -150, 125}, // 6
    {150, -120, 125}, // 6
    {-150, -120, 125}, // 7
    {-150, -150, 125}, // 7
    {-150, -120, 125}, // 7
    {-150, -120, -125}
};

void mouseMotionCallback(int x_pos, int y_pos);
void mouseButtonCallback(int button, int state, int x, int y);
void display();
void reshape(int _width, int _height);
void idle();
void keyboardFunc(unsigned char key, int x, int y);
void draw_contour();
void draw_fill();
void draw_full();

void clearColor(const glm::vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Fomichev Dmitriy lab1");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    clearColor(colorPalette::PINKGREY);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMouseFunc(mouseButtonCallback);
    glutMotionFunc(mouseMotionCallback);
    glutKeyboardFunc(keyboardFunc);
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glutMainLoop();

    return 0;
}

void draw_contour()
{
    step.draw_contour(colorPalette::BLACK, width_line);
    slab_contour.draw_contour(colorPalette::BLACK, width_line);
    background_wall.draw_contour(colorPalette::BLACK, width_line);
    left_top_base.draw_contour(colorPalette::BLACK, width_line);
    left_top_base.draw_contour(colorPalette::BLACK, width_line, {229, 0.f, 0.f});
    left_top_base.draw_contour(colorPalette::BLACK, width_line, {0.f, 0.f, 193.f});
    left_top_base.draw_contour(colorPalette::BLACK, width_line, {229, 0.f, 193.f});
    left_top_base.draw_contour(colorPalette::BLACK, width_line, {0.f, -230.f, 0.f});
    left_top_base.draw_contour(colorPalette::BLACK, width_line, {229, -230.f, 0.f});
    left_top_base.draw_contour(colorPalette::BLACK, width_line, {0.f, -230.f, 193.f});
    left_top_base.draw_contour(colorPalette::BLACK, width_line, {229, -230.f, 193.f});
    roof.draw_contour(colorPalette::BLACK, width_line);
    wall.draw_contour(colorPalette::BLACK, width_line);
    wall.draw_contour(colorPalette::BLACK, width_line, {229.f, 0.f, 0.f});
    left_column.draw_contour(camera, colorPalette::BLACK, width_line);
    left_column.draw_contour(camera, colorPalette::BLACK, width_line, {228.f, 0.f, 0.f});
    left_column.draw_contour(camera, colorPalette::BLACK, width_line, {228.f, 0.f, 192.f});
    left_column.draw_contour(camera, colorPalette::BLACK, width_line, {0.f, 0.f, 192.f});
}

void draw_fill()
{
    slab.draw(colorPalette::GREY);
    step.draw(colorPalette::GREY);
    block.draw(colorPalette::GREY);
    block.draw(colorPalette::GREY, {200, 0, 0});
    background_wall.draw(colorPalette::WHITE);
    left_top_base.draw(colorPalette::WHITE);
    left_top_base.draw(colorPalette::WHITE, {229, 0.f, 0.f});
    left_top_base.draw(colorPalette::WHITE, {0.f, 0.f, 193.f});
    left_top_base.draw(colorPalette::WHITE, {229, 0.f, 193.f});
    left_top_base.draw(colorPalette::WHITE, {0.f, -230.f, 0.f});
    left_top_base.draw(colorPalette::WHITE, {229, -230.f, 0.f});
    left_top_base.draw(colorPalette::WHITE, {0.f, -230.f, 193.f});
    left_top_base.draw(colorPalette::WHITE, {229, -230.f, 193.f});
    roof.draw(colorPalette::GREY);
    wall.draw(colorPalette::WHITE);
    wall.draw(colorPalette::WHITE, {229.f, 0.f, 0.f});
    left_column.draw(colorPalette::WHITE);
    left_column.draw(colorPalette::WHITE, {228.f, 0.f, 0.f});
    left_column.draw(colorPalette::WHITE, {228.f, 0.f, 192.f});
    left_column.draw(colorPalette::WHITE, {0.f, 0.f, 192.f});
}

void draw_full()
{
    slab.draw(colorPalette::GREY);
    step.draw_full(colorPalette::GREY, colorPalette::BLACK, width_line);
    block.draw(colorPalette::GREY);
    block.draw(colorPalette::GREY, {200, 0, 0});
    slab_contour.draw_contour(colorPalette::BLACK, width_line);
    background_wall.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line);
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line);
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {229, 0.f, 0.f});
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {0.f, 0.f, 193.f});
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {229, 0.f, 193.f});
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {0.f, -230.f, 0.f});
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {229, -230.f, 0.f});
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {0.f, -230.f, 193.f});
    left_top_base.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {229, -230.f, 193.f});
    roof.draw_full(colorPalette::GREY, colorPalette::BLACK, width_line);
    wall.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line);
    wall.draw_full(colorPalette::WHITE, colorPalette::BLACK, width_line, {229.f, 0.f, 0.f});
    left_column.draw_full(camera, colorPalette::WHITE, colorPalette::BLACK, width_line);
    left_column.draw_full(camera, colorPalette::WHITE, colorPalette::BLACK, width_line, {228.f, 0.f, 0.f});
    left_column.draw_full(camera, colorPalette::WHITE, colorPalette::BLACK, width_line, {228.f, 0.f, 192.f});
    left_column.draw_full(camera, colorPalette::WHITE, colorPalette::BLACK, width_line, {0.f, 0.f, 192.f});
}

void keyboardFunc(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'C': case 'c':
        case 'с': case 'С':
        {
            static int count = 0;
            if (count == 0) 
            {
                camera.setCameraAngle(std::numbers::pi_v<float> / 2.f - 0.0001f, 0.f);
                count++;
            }
            else if (count == 1)
            {
                camera.setCameraAngle(3.f * std::numbers::pi_v<float> / 2.f - 0.0001f, 0.f);
                count = 0;
            }
            break;
        }
        case 'V': case 'v':
        case 'м' : case 'М':
        {
            static int count = 0;
            if (count == 0) 
            {
                camera.setCameraAngle(0.f, 0.f);
                count++;
            }
            else if (count == 1)
            {
                camera.setCameraAngle(0.f, std::numbers::pi_v<float>);
                count = 0;
            }
            break;
        }
        case 'X': case 'x':
        case 'ч' : case 'Ч':
        {
            static int count = 1;
            if (count == 1)
            {
                curMode = RenderMode::FILL;
                count++;
            }
            else if (count == 2)
            {
                curMode = RenderMode::CONTOUR;
                count = 0;
            }
            else
            {
                curMode = RenderMode::FULL;
                count++;
            }
            break;
        }

    };
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.applyProjection(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    camera.applyView();
    
    switch(curMode)
    {
        case RenderMode::FULL:
        {
            draw_full();
            break;
        }
        case RenderMode::FILL:
        {
            draw_fill();
            break;
        }
        case RenderMode::CONTOUR:
        {
            draw_contour();
            break;
        }
    };

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    height = height > 0 ? height : 1;

    glViewport(0, 0, width, height);

    camera.applyProjection(width, height);
}

void idle()
{
    glutPostRedisplay();
}

void mouseMotionCallback(int x_pos, int y_pos)
{
    if (!mouseCapture) return;

    if (firstMouse) 
    {
        last_X = x_pos;
        last_Y = y_pos;
        firstMouse = false;
    }

    float delta_X = static_cast<float>(x_pos) - last_X;
    float delta_Y = last_Y - static_cast<float>(y_pos);

    last_X = x_pos;
    last_Y = y_pos;

    camera.rotate(delta_X, delta_Y);
}

void mouseButtonCallback(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON) return;

    if (state == GLUT_DOWN)
    {
        mouseCapture = true;
        firstMouse = true;
        glutSetCursor(GLUT_CURSOR_NONE);
        last_X = x;
        last_Y = y;
    }
    else if (state == GLUT_UP)
    {
        mouseCapture = false;
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
}