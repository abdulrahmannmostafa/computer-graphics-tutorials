#include <GL/glut.h>
#include <stdio.h>
#include "hsv_utils.h"

int main()
{
    float h, s, v, r, g, b;

    rgbToHSV(45, 215, 0, h, s, v);
    printf("RGB(45,215,0)   -> HSV(%.2f, %.2f, %.2f)\n", h, s, v);

    hsvToRGB(280, 50, 90, r, g, b);
    printf("HSV(280,50,90)  -> RGB(%.0f, %.0f, %.0f)\n", r, g, b);

    rgbToHSV(255, 0, 0, h, s, v);
    printf("RGB(255,0,0)    -> HSV(%.0f, %.0f, %.0f)\n", h, s, v);

    rgbToHSV(128, 128, 0, h, s, v);
    printf("RGB(128,128,0)  -> HSV(%.0f, %.0f, %.1f)\n", h, s, v);

    rgbToHSV(255, 0, 255, h, s, v);
    printf("RGB(255,0,255)  -> HSV(%.0f, %.0f, %.0f)\n", h, s, v);
    return 0;
}
