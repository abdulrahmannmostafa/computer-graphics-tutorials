#include <GL/glut.h>

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;

void init2D()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
    glShadeModel(GL_SMOOTH); // interpolate colors between vertices (this is the default)
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 1) Triangle: one color per vertex
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // red
    glVertex2i(10, 40);
    glColor3f(0.0, 1.0, 0.0); // green
    glVertex2i(45, 40);
    glColor3f(0.0, 0.0, 1.0); // blue
    glVertex2i(27, 90);
    glEnd();

    // 2) Quad: four different corners
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0); // yellow
    glVertex2i(55, 40);
    glColor3f(0.0, 1.0, 1.0); // cyan
    glVertex2i(90, 40);
    glColor3f(1.0, 0.0, 1.0); // magenta
    glVertex2i(90, 90);
    glColor3f(1.0, 1.0, 1.0); // white
    glVertex2i(55, 90);
    glEnd();

    // 3) Gray ramp: only the two end colors are given
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0); // black
    glVertex2i(10, 10);
    glVertex2i(10, 25);
    glColor3f(1.0, 1.0, 1.0); // white
    glVertex2i(90, 25);
    glVertex2i(90, 10);
    glEnd();

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Smooth shading");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
