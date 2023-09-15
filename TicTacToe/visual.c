#include <glad/glad.h>
#include "visual.h"

#pragma comment(lib, "opengl32.lib")

void DrawGrid()
{

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.87f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.87f, -0.5f);

    glEnd();
}