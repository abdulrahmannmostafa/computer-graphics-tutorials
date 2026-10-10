#include <GL/glut.h>
#include <math.h>
#include <string.h>

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;


void printSome(const char *str, float x, float y)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
}


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


void init2D()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // sky: dark blue at the top -> orange at the horizon (two colors, OpenGL interpolates)
    glBegin(GL_QUADS);
    glColor3f(0.10, 0.10, 0.45);
    glVertex2i(0, 100);
    glVertex2i(100, 100);
    glColor3f(1.00, 0.55, 0.20);
    glVertex2i(100, 35);
    glVertex2i(0, 35);
    glEnd();

    // sun: warm yellow disc, half hidden behind the ground
    glColor3f(1.0, 0.85, 0.30);
    DrawCircle(50, 38, 14, 100);

    // far mountains (dark purple, lighter at the peak)
    glBegin(GL_TRIANGLES);
    glColor3f(0.35, 0.15, 0.35);
    glVertex2i(0, 35);
    glVertex2i(30, 35);
    glColor3f(0.55, 0.30, 0.45);
    glVertex2i(14, 62);
    glColor3f(0.35, 0.15, 0.35);
    glVertex2i(65, 35);
    glVertex2i(100, 35);
    glColor3f(0.55, 0.30, 0.45);
    glVertex2i(84, 58);
    glEnd();

    // ground: dark green -> almost black at the bottom
    glBegin(GL_QUADS);
    glColor3f(0.10, 0.25, 0.12);
    glVertex2i(0, 35);
    glVertex2i(100, 35);
    glColor3f(0.0, 0.03, 0.02);
    glVertex2i(100, 0);
    glVertex2i(0, 0);
    glEnd();

    printSome("Sunset", 44, 10);

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Task 4 - Sunset");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
