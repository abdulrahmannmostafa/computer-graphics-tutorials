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
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void init2D()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // light is added to BLACK
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
    glEnable(GL_BLEND);          // enable blending for additive mixing
    glBlendFunc(GL_ONE, GL_ONE); // result = source + destination  (additive)
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // red
    DrawCircle(40, 58, 22, 100);
    glColor3f(0.0, 1.0, 0.0); // green
    DrawCircle(60, 58, 22, 100);
    glColor3f(0.0, 0.0, 1.0); // blue
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
    glutCreateWindow("Additive mixing (RGB)");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
