#include <glad/glad.h>
#include <math.h>
#include "visual.h"
#include "game.h"

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#pragma comment(lib, "opengl32.lib")

float CELL_SIZE = 2.0f / (float)FIELD_SIZE;
float HALF_CELL_SIZE = 1.0f / (float)FIELD_SIZE;

void DrawCell(CellState);
void DrawCross();
void DrawZero();
void DrawCircle(float, int);

void DrawMain()
{
    glLineWidth(2.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);

    for (int i = 1; i < FIELD_SIZE; ++i)
    {
        float x = -1.0f + HALF_CELL_SIZE * i * 2;
        glVertex2f(x, -1.0f); glVertex2f(x, 1.0f);
    }

    for (int j = 1; j < FIELD_SIZE; ++j)
    {
        float y = -1.0f + HALF_CELL_SIZE * j * 2;
        glVertex2f(-1.0f, y); glVertex2f(1.0f, y);
    }

    glEnd();

    for (int i = 0; i < FIELD_SIZE; ++i)
        for (int j = 0; j < FIELD_SIZE; ++j)
        {
            glPushMatrix();

                glTranslatef(-1.0f + HALF_CELL_SIZE + HALF_CELL_SIZE * i * 2.0f, -1.0f + HALF_CELL_SIZE + HALF_CELL_SIZE * j * 2.0f, 0.0f);
                glScalef(HALF_CELL_SIZE, HALF_CELL_SIZE, HALF_CELL_SIZE);

                DrawCell(matrix[i][j]);

            glPopMatrix();
        }

    if (gameOverType)
    {
        glColor3f(0.3f, 1.0f, 0.3f);
        glBegin(GL_LINES);

        switch (gameOverType)
        {
        case Horizontal:
        {
            float y = -1.0f + HALF_CELL_SIZE + HALF_CELL_SIZE * gameOverInfo * 2.0f;
            glVertex2f(-1.0f, y); glVertex2f(1.0f, y);
            break;
        }

        case Vertical:
        {
            float x = -1.0f + HALF_CELL_SIZE + HALF_CELL_SIZE * gameOverInfo * 2.0f;
            glVertex2f(x, -1.0f); glVertex2f(x, 1.0f);
            break;
        }

        case Diagonal:
        {
            if (gameOverInfo)
            {
                glVertex2f(-1.0f, -1.0f); glVertex2f(1.0f, 1.0f);
            }
            else
            {
                glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
            }
            break;
        }
        }

        glEnd();
    }

    switch (aiType)
    {
    case Easy:
        glColor3f(0.2f, 1.0f, 0.2f);
        break;
    case Medium:
        glColor3f(1.0f, 0.5f, 0.0f);
        break;
    case Hard:
        glColor3f(1.0f, 0.2f, 0.2f);
        break;
    }

    glBegin(GL_TRIANGLE_STRIP);

        glVertex2f(-1.0f, 1.0f); glVertex2f(-0.9f, 1.0f);
        glVertex2f(-1.0f, 0.95f); glVertex2f(-0.9f, 0.95f);

    glEnd();
}

void DrawCell(CellState state)
{
    if (!state) return;

    if (state == Cross)
        DrawCross();
    else
        DrawZero();
}

void DrawCross()
{
    glColor3f(1.0f, 0.3f, 0.3f);

    glPushMatrix();

        glScalef(0.7f, 0.7f, 0.7f);

        glBegin(GL_LINES);

            glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
            glVertex2f(-1.0f, -1.0f); glVertex2f(1.0f, 1.0f);

        glEnd();

    glPopMatrix();
}

void DrawZero()
{
    glColor3f(0.3f, 0.3f, 1.0f);
    DrawCircle(0.66f, 30);
}

void DrawCircle(float radius, int segments)
{
    glBegin(GL_LINE_LOOP);

        for (int i = 0; i < segments; ++i)
        {
            float theta = 2.0f * M_PI * (float)i / (float)segments;

            float x = radius * cosf(theta);
            float y = radius * sinf(theta);

            glVertex2f(x, y);
        }

    glEnd();
}

void Rescale(int width, int height)
{
    int size = width > height ? height : width;
    glViewport((width - size) / 2, (height - size) / 2, size, size);
}