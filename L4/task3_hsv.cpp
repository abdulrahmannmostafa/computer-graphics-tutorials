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


// one horizontal strip of 360 thin quads; mode 0 = hue, 1 = saturation, 2 = value
void DrawStrip(float y0, float y1, int mode, float fixedHue)
{
    float x0 = 5, width = 90;
    int n = 360;
    float qw = width / n;
    glBegin(GL_QUADS);
    for (int i = 0; i < n; i++)
    {
        float t = i / (float)(n - 1); // 0 ... 1 along the strip
        if (mode == 0) setColorHSV(i, 100, 100);
        if (mode == 1) setColorHSV(fixedHue, t * 100, 100);
        if (mode == 2) setColorHSV(fixedHue, 100, t * 100);
        glVertex2f(x0 + i * qw, y0);
        glVertex2f(x0 + (i + 1) * qw, y0);
        glVertex2f(x0 + (i + 1) * qw, y1);
        glVertex2f(x0 + i * qw, y1);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawStrip(72, 88, 0, 0);
    printSome("Hue 0 -> 360  (S = 100, V = 100)", 5, 91);

    DrawStrip(46, 62, 1, 280);
    printSome("Saturation 0 -> 100  (H = 280, V = 100)", 5, 65);

    DrawStrip(20, 36, 2, 280);
    printSome("Value 0 -> 100  (H = 280, S = 100)", 5, 39);

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Task 3 - HSV strips");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
