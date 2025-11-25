#ifndef SHAPE_H
#define SHAPE_H

#include "../include/engine.h"

void draw_line(int x0, int y0, int x1, int y1, unsigned char color);
void draw_rect(int x, int y, int w, int h, unsigned char color, int filled);
void draw_circle(int x0, int y0, int radius, unsigned char color, int filled);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2,
                   unsigned char color, int filled);
void draw_polygon(const int *x_points, const int *y_points, int num_points,
                  unsigned char color, int filled);

#endif
