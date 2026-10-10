#include <GL/glut.h>
#include <math.h>

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;

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

// OpenGL only knows RGB, so a CMY ink is converted with  R = 1-C, G = 1-M, B = 1-Y
void setColorCMY(float c, float m, float y)
{
    glColor3f(1.0 - c, 1.0 - m, 1.0 - y);
}

void init2D()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // inks are printed on WHITE paper
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_DST_COLOR, GL_ZERO); // result = source * destination (a filter)
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    setColorCMY(1, 0, 0); // cyan
    DrawCircle(40, 58, 22, 100);
    setColorCMY(0, 1, 0); // magenta
    DrawCircle(60, 58, 22, 100);
    setColorCMY(0, 0, 1); // yellow
    DrawCircle(50, 40, 22, 100);

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Subtractive mixing (CMY)");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
