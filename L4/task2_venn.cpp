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
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}


void setColorCMY(float c, float m, float y)
{
    glColor3f(1.0 - c, 1.0 - m, 1.0 - y);
}

void DrawRect(float x0, float y0, float x1, float y1)
{
    glBegin(GL_QUADS);
    glVertex2f(x0, y0);
    glVertex2f(x1, y0);
    glVertex2f(x1, y1);
    glVertex2f(x0, y1);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // backgrounds (no blending): black screen on the left, white paper on the right
    glDisable(GL_BLEND);
    glColor3f(0, 0, 0);
    DrawRect(0, 0, 50, 100);
    glColor3f(1, 1, 1);
    DrawRect(50, 0, 100, 100);

    // LEFT: additive RGB  ->  result = src + dst
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glColor3f(1, 0, 0);
    DrawCircle(19, 62, 12, 100);
    glColor3f(0, 1, 0);
    DrawCircle(31, 62, 12, 100);
    glColor3f(0, 0, 1);
    DrawCircle(25, 50, 12, 100);

    // RIGHT: subtractive CMY  ->  result = src * dst
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    setColorCMY(1, 0, 0);
    DrawCircle(69, 62, 12, 100);
    setColorCMY(0, 1, 0);
    DrawCircle(81, 62, 12, 100);
    setColorCMY(0, 0, 1);
    DrawCircle(75, 50, 12, 100);

    glDisable(GL_BLEND);
    printSome("Additive (light)", 10, 25);
    printSome("RGB -> white", 14, 18);
    glColor3f(0, 0, 0);
    glRasterPos2f(60, 25);
    const char *t1 = "Subtractive (ink)";
    for (int i = 0; i < strlen(t1); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, t1[i]);
    glRasterPos2f(64, 18);
    const char *t2 = "CMY -> black";
    for (int i = 0; i < strlen(t2); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, t2[i]);

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Task 2 - additive vs subtractive");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
