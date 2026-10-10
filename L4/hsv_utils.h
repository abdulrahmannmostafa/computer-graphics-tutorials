// ---- RGB <-> HSV (same formulas as the lecture) ----
// RGB are in 0..255, H in degrees (0..360), S and V in percent (0..100)
#include <math.h>

void rgbToHSV(float r, float g, float b, float &h, float &s, float &v)
{
    r /= 255.0; g /= 255.0; b /= 255.0;                       // 1) divide by 255
    float cmax = fmaxf(r, fmaxf(g, b));                       // 2) cmax, cmin, diff
    float cmin = fminf(r, fminf(g, b));
    float diff = cmax - cmin;

    if (diff == 0)        h = 0;                              // 3) hue
    else if (cmax == r)   h = fmodf(60 * ((g - b) / diff) + 360, 360);
    else if (cmax == g)   h = fmodf(60 * ((b - r) / diff) + 120, 360);
    else                  h = fmodf(60 * ((r - g) / diff) + 240, 360);

    s = (cmax == 0) ? 0 : (diff / cmax) * 100;                // 4) saturation
    v = cmax * 100;                                           // 5) value
}

void hsvToRGB(float h, float s, float v, float &r, float &g, float &b)
{
    h = fmodf(h, 360); if (h < 0) h += 360;
    s /= 100.0; v /= 100.0;

    float C = v * s;
    float X = C * (1 - fabsf(fmodf(h / 60.0, 2) - 1));
    float m = v - C;

    float r1, g1, b1;
    if      (h < 60)  { r1 = C; g1 = X; b1 = 0; }
    else if (h < 120) { r1 = X; g1 = C; b1 = 0; }
    else if (h < 180) { r1 = 0; g1 = C; b1 = X; }
    else if (h < 240) { r1 = 0; g1 = X; b1 = C; }
    else if (h < 300) { r1 = X; g1 = 0; b1 = C; }
    else              { r1 = C; g1 = 0; b1 = X; }

    r = (r1 + m) * 255;
    g = (g1 + m) * 255;
    b = (b1 + m) * 255;
}

// convenience: set the OpenGL color directly from an HSV value
void setColorHSV(float h, float s, float v)
{
    float r, g, b;
    hsvToRGB(h, s, v, r, g, b);
    glColor3f(r / 255.0, g / 255.0, b / 255.0);
}
