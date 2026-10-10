#include <GL/glut.h>
#include <math.h>
#include <string.h>

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;

#include "hsv_utils.h"

void printSome(const char *str, float x, float y)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
}

void init2D()
{
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}

// Hue goes around the circle, saturation goes from the center (0) to the edge (100)
void DrawColorWheel(float cx, float cy, float r, float value)
{
    int n = 360; // one thin triangle per degree of hue
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < n; i++)
    {
        float a0 = 2 * 3.1415926f * i / n;       // angle of the current triangle
        float a1 = 2 * 3.1415926f * (i + 1) / n; // angle of the next triangle

        setColorHSV(i, 0, value); // center: no saturation
        glVertex2f(cx, cy);
        setColorHSV(i, 100, value);                       // edge: full saturation
        glVertex2f(cx + r * cosf(a0), cy + r * sinf(a0)); // vertex at the edge of the current triangle (edge point of triangle 1)
        setColorHSV(i + 1, 100, value);
        glVertex2f(cx + r * cosf(a1), cy + r * sinf(a1)); // vertex at the edge of the next triangle (edge point of triangle 2)
    }
    glEnd();
}

// Fixed hue: saturation increases to the right, value increases upwards
void DrawSVGrid(float x0, float y0, float w, float h, float hue, int cells)
{
    float cw = w / cells, ch = h / cells;
    glBegin(GL_QUADS);
    for (int i = 0; i < cells; i++)
        for (int j = 0; j < cells; j++)
        {
            setColorHSV(hue, 100.0 * i / (cells - 1), 100.0 * j / (cells - 1));
            glVertex2f(x0 + i * cw, y0 + j * ch);
            glVertex2f(x0 + (i + 1) * cw, y0 + j * ch);
            glVertex2f(x0 + (i + 1) * cw, y0 + (j + 1) * ch);
            glVertex2f(x0 + i * cw, y0 + (j + 1) * ch);
        }
    glEnd();
}

void DrawSwatch(float x, float y, float w, float h)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawColorWheel(30, 62, 26, 100);
    printSome("Hue (angle) / Saturation (radius)", 6, 92);

    DrawSVGrid(64, 42, 32, 40, 280, 8);
    printSome("H = 280", 64, 86);
    printSome("S ->", 80, 36);
    printSome("V", 58, 62);

    // complementary pair: H and H + 180
    setColorHSV(280, 100, 100);
    DrawSwatch(10, 8, 18, 18);
    setColorHSV(280 + 180, 100, 100);
    DrawSwatch(32, 8, 18, 18);
    printSome("H = 280 and its complement", 10, 30);
    printSome("H = 100", 33, 3);
    printSome("V = 100", 58, 3);
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("HSV color wheel");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
