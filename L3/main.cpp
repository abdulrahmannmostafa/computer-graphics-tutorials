#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

int xc = 0, yc = 0, r = 100; // circle center and radius
const int WIN_SIZE = 500;

// Plot the 8 symmetric points of (x , y) around the center (xc , yc)
void plotSymmetric(int x, int y)
{
    glVertex2i(xc + x, yc + y); // (x, y)
    glVertex2i(xc - x, yc + y); // (-x, y)
    glVertex2i(xc + x, yc - y); // (x, -y)
    glVertex2i(xc - x, yc - y); // (-x, -y)
    glVertex2i(xc + y, yc + x); // (y, x)
    glVertex2i(xc - y, yc + x); // (-y, x)
    glVertex2i(xc + y, yc - x); // (y, -x)
    glVertex2i(xc - y, yc - x); // (-y, -x)
}

void midpointCircle()
{
    int x = 0, y = r; // first point (0 , r)
    int p = 1 - r;    // initial decision parameter

    glBegin(GL_POINTS);
    plotSymmetric(x, y);

    while (x < y)
    {
        x++; // x_{k+1} = x_k + 1
        if (p < 0)
        {
            p += 2 * x + 1; // y stays the same
        }
        else
        {
            y--; // y_{k+1} = y_k - 1
            p += 2 * x + 1 - 2 * y;
        }
        plotSymmetric(x, y);
    }
    glEnd();
}

void textDisplay()
{
    glColor3f(0.0f, 0.0f, 0.0f); // black color for text
    glRasterPos2i(-WIN_SIZE / 2 + 10, WIN_SIZE / 2 - 20);
    const char *text = "Midpoint Circle Algorithm";
    for (int i = 0; i < strlen(text); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // axes (light gray)
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    glVertex2i(-WIN_SIZE / 2, 0);
    glVertex2i(WIN_SIZE / 2, 0);
    glVertex2i(0, -WIN_SIZE / 2);
    glVertex2i(0, WIN_SIZE / 2);
    glEnd();

    // circle (red points)
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(3.0f); // magnify the points for better visibility
    midpointCircle();

    textDisplay();

    glFlush();
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WIN_SIZE / 2, WIN_SIZE / 2, -WIN_SIZE / 2, WIN_SIZE / 2);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIN_SIZE, WIN_SIZE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}