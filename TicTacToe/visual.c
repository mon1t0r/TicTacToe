#include <glad/glad.h>
#include "visual.h"

#pragma comment(lib, "opengl32.lib")

void DrawGrid()
{
    glLineWidth(2.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);

    glVertex2f(-1.0f, 0.333f); glVertex2f(1.0f, 0.333f);
    glVertex2f(-1.0f, -0.333f); glVertex2f(1.0f, -0.333f);

    glVertex2f(-0.333f, 1.0f); glVertex2f(-0.333f, -1.0f);
    glVertex2f(0.333f, 1.0f); glVertex2f(0.333f, -1.0f);

    glEnd();
}