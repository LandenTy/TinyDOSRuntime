/*
                                  Shape.C

        Will be refactored into an immediate mode GUI Library for
                                TinyDOSEngine.
*/
#include <stdlib.h>
#include "../include/shape.h"

/*
    function : draw_line
    args     : x0, y0, x1, y1, color
    purpose  : Draws a line from (x0, y0) to (x1, y1) with a color
      
      x      :           (Int)          X-Position
      y      :           (Int)          Y-Position
      w      :           (Int)            Width
      h      :           (Int)            Height
    color    :      (unsigned char)    Color (8bpp)
*/
void draw_line(int x0, int y0, int x1, int y1, unsigned char color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    for (;;) {
        putpixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

/*
    function : draw_rect
    args     : x, y, w, h, color, filled
    purpose  : Draws a rectangle at (x,y) with width and height using color.
    You can also set options for if the rectangle is filled or not.

      x      :           (Int)          X-Position
      y      :           (Int)          Y-Position
      w      :           (Int)            Width
      h      :           (Int)            Height
    color    :      (unsigned char)    Color (8bpp)
    filled   :           (Int)           isFilled?
*/
void draw_rect(int x, int y, int w, int h, unsigned char color, int filled) {
    int i, j;
    if (filled) {
        for (j = y; j < y + h; ++j)
            for (i = x; i < x + w; ++i)
                putpixel(i, j, color);
    } else {
        draw_line(x, y, x + w - 1, y, color);
        draw_line(x, y, x, y + h - 1, color);
        draw_line(x + w - 1, y, x + w - 1, y + h - 1, color);
        draw_line(x, y + h - 1, x + w - 1, y + h - 1, color);
    }
}

/*
    function : draw_circle
    args     : xc, yc, r, color, filled
    purpose  : Draws a circle at (x,y) with radius using color.
    You can also set options for if the circle is filled or not.

      x      :           (Int)          X-Position
      y      :           (Int)          Y-Position
      r      :           (Int)            Radius
    color    :      (unsigned char)    Color (8bpp)
    filled   :           (Int)           isFilled?
*/
void draw_circle(int xc, int yc, int r, unsigned char color, int filled) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        if (filled) {
            draw_line(xc - x, yc - y, xc + x, yc - y, color);
            draw_line(xc - y, yc - x, xc + y, yc - x, color);
            draw_line(xc - y, yc + x, xc + y, yc + x, color);
            draw_line(xc - x, yc + y, xc + x, yc + y, color);
        } else {
            putpixel(xc + x, yc + y, color);
            putpixel(xc - x, yc + y, color);
            putpixel(xc + x, yc - y, color);
            putpixel(xc - x, yc - y, color);
            putpixel(xc + y, yc + x, color);
            putpixel(xc - y, yc + x, color);
            putpixel(xc + y, yc - x, color);
            putpixel(xc - y, yc - x, color);
        }

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

/*
    function : draw_triangle
    args     : x1, y1, x2, y2, x3, y3, color, filled
    purpose  : Draws a triangle from (x1, y1) to (x2, y2) to
    (x3, y3) using color. You can also set options for if the 
    triangle is filled or not.

      x      :           (Int)          X-Position
      y      :           (Int)          Y-Position
      r      :           (Int)            Radius
    color    :      (unsigned char)    Color (8bpp)
    filled   :           (Int)           isFilled?
*/
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
                   unsigned char color, int filled)
{
    int tmp;

    if (!filled) {
        draw_line(x1, y1, x2, y2, color);
        draw_line(x2, y2, x3, y3, color);
        draw_line(x3, y3, x1, y1, color);
        return;
    }

    if (y2 < y1) { tmp = y1; y1 = y2; y2 = tmp; tmp = x1; x1 = x2; x2 = tmp; }
    if (y3 < y1) { tmp = y1; y1 = y3; y3 = tmp; tmp = x1; x1 = x3; x3 = tmp; }
    if (y3 < y2) { tmp = y2; y2 = y3; y3 = tmp; tmp = x2; x2 = x3; x3 = tmp; }

    {
        int total_height = y3 - y1;
        int i;
        for (i = 0; i < total_height; i++) {
            int second_half = i > (y2 - y1) || y2 == y1;
            int segment_height = second_half ? (y3 - y2) : (y2 - y1);
            float alpha = (float)i / total_height;
            float beta = (float)(i - (second_half ? (y2 - y1) : 0)) / segment_height;

            int Ax = x1 + (int)((x3 - x1) * alpha);
            int Bx = second_half
                        ? x2 + (int)((x3 - x2) * beta)
                        : x1 + (int)((x2 - x1) * beta);

            if (Ax > Bx) { tmp = Ax; Ax = Bx; Bx = tmp; }

            draw_line(Ax, y1 + i, Bx, y1 + i, color);
        }
    }
}

/*
    function : draw_polygon
    args     : x[], y[], n, color, filled
    purpose  : Draws a polygon from (x[0]-x[n],y[0]-y[n]) 
    with n number of indices, and using color. 
    You can also set options for if the polygon is 
    filled or not.

     x[]     :           (Int)          List of Xs
     y[]     :           (Int)          List of Ys
      n      :           (Int)         # of indices
    color    :      (unsigned char)    Color (8bpp)
    filled   :           (Int)           isFilled?
*/
void draw_polygon(const int *x, const int *y, int n,
                  unsigned char color, int filled)
{
    int i, j, k;
    int min_y, max_y;

    if (n < 3)
        return;

    for (i = 0; i < n; i++) {
        j = (i + 1) % n;
        draw_line(x[i], y[i], x[j], y[j], color);
    }

    if (!filled)
        return;

    min_y = y[0];
    max_y = y[0];
    for (i = 1; i < n; i++) {
        if (y[i] < min_y) min_y = y[i];
        if (y[i] > max_y) max_y = y[i];
    }

    for (i = min_y; i <= max_y; i++) {
        int nodes[64];
        int nodes_count = 0;

        j = n - 1;
        for (k = 0; k < n; k++) {
            if ((y[k] < i && y[j] >= i) || (y[j] < i && y[k] >= i)) {
                int x_int = x[k] + (i - y[k]) * (x[j] - x[k]) / (y[j] - y[k]);
                nodes[nodes_count++] = x_int;
            }
            j = k;
        }

        for (j = 0; j < nodes_count - 1; j++) {
            for (k = j + 1; k < nodes_count; k++) {
                if (nodes[j] > nodes[k]) {
                    int temp = nodes[j];
                    nodes[j] = nodes[k];
                    nodes[k] = temp;
                }
            }
        }

        for (j = 0; j < nodes_count; j += 2) {
            if (j + 1 < nodes_count)
                draw_line(nodes[j], i, nodes[j + 1], i, color);
        }
    }
}
