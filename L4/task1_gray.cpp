#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

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


void init2D()
{
    glClearColor(0.25, 0.25, 0.25, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int steps = 8;
    float w = 10; // width of each step
    for (int i = 0; i < steps; i++)
    {
        float gray = i / (float)(steps - 1); // 0.0 ... 1.0  (R = G = B -> main diagonal of the RGB cube)
        float x = 10 + i * w;

        glColor3f(gray, gray, gray);
        glBegin(GL_QUADS);
        glVertex2f(x, 40);
        glVertex2f(x + w, 40);
        glVertex2f(x + w, 70);
        glVertex2f(x, 70);
        glEnd();

        char label[16];
        sprintf(label, "%.2f", gray);
        printSome(label, x + 1.5, 33);
    }
    printSome("8 gray levels: (g, g, g)", 10, 80);

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Task 1 - gray ramp");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
