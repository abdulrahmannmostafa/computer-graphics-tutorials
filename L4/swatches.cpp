#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;

// the 8 corners of the RGB cube
float colors[8][3] = {
    {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
    {1, 1, 0}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
const char *names[8] = {"Black (0,0,0)",   "Red (1,0,0)",     "Green (0,1,0)",
                        "Blue (0,0,1)",    "Yellow (1,1,0)",  "Cyan (0,1,1)",
                        "Magenta (1,0,1)", "White (1,1,1)"};

void printSome(const char *str, int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2d(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
}

void init2D()
{
    glClearColor(0.25, 0.25, 0.25, 1.0); // dark gray background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 8; i++)
    {
        int col = i % 4;
        int row = i / 4;
        float x = 8 + col * 22;
        float y = 55 - row * 35;

        glColor3f(colors[i][0], colors[i][1], colors[i][2]); // set the current color
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + 18);
        glVertex2f(x + 18, y + 18);
        glVertex2f(x + 18, y);
        glEnd();

        printSome(names[i], x, y - 5);
    }
    glutSwapBuffers();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("RGB swatches");
    init2D();
    glutDisplayFunc(display);
    glutMainLoop();
}
