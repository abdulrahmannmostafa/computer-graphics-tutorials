#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "hsv_utils.h"

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;

float hue = 0; // current hue in degrees

void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        glVertex2f(r * cosf(theta) + cx, r * sinf(theta) + cy);
    }
    glEnd();
}

void printSome(const char *str, float x, float y)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'd') hue += 10;
    if (key == 'a') hue -= 10;
    glutPostRedisplay(); // ask GLUT to call display() again
}

void init2D()
{
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    setColorHSV(hue, 100, 100); // current hue
    DrawCircle(30, 55, 18, 100);

    setColorHSV(hue + 180, 100, 100); // complement
    glBegin(GL_QUADS);
    glVertex2f(52, 37);
    glVertex2f(88, 37);
    glVertex2f(88, 73);
    glVertex2f(52, 73);
    glEnd();

    char text[64];
    sprintf(text, "Hue = %.0f   (A / D to rotate)", fmodf(hue + 360 * 100, 360));
    printSome(text, 25, 15);

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Bonus - rotate the hue");
    init2D();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
