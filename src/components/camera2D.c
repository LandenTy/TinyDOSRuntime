#include "../../include/components/camera2D.h"
#include <math.h>

void Camera2D_Init(Camera2D* cam, float x, float y, float viewW, float viewH)
{
    cam->x = x;
    cam->y = y;
    cam->zoom = 1.0f;
    cam->angle = 0.0f;
    cam->halfW = viewW * 0.5f;
    cam->halfH = viewH * 0.5f;
}

void Camera2D_Move(Camera2D* cam, float dx, float dy)
{
    cam->x += dx;
    cam->y += dy;
}

void Camera2D_SetPosition(Camera2D* cam, float x, float y)
{
    cam->x = x;
    cam->y = y;
}

void Camera2D_SetZoom(Camera2D* cam, float zoom)
{
    if (zoom < 0.01f) {
        zoom = 0.01f;
    }
    cam->zoom = zoom;
}

void Camera2D_SetAngle(Camera2D* cam, float angle)
{
    cam->angle = angle;
}

void Camera2D_WorldToScreen(Camera2D* cam, float wx, float wy, float* sx, float* sy)
{
    float x;
    float y;
    float c;
    float s;
    float rx;
    float ry;

    /* Translate */
    x = wx - cam->x;
    y = wy - cam->y;

    /* Rotate (cos/sin only, no cosf/sinf in Watcom) */
    c = (float)cos(-cam->angle);
    s = (float)sin(-cam->angle);

    rx = x * c - y * s;
    ry = x * s + y * c;

    /* Zoom */
    rx *= cam->zoom;
    ry *= cam->zoom;

    /* Center to viewport */
    *sx = rx + cam->halfW;
    *sy = ry + cam->halfH;
}

void Camera2D_ScreenToWorld(Camera2D* cam, float sx, float sy, float* wx, float* wy)
{
    float x;
    float y;
    float c;
    float s;
    float rx;
    float ry;

    /* Offset */
    x = sx - cam->halfW;
    y = sy - cam->halfH;

    /* Unzoom */
    x /= cam->zoom;
    y /= cam->zoom;

    c = (float)cos(cam->angle);
    s = (float)sin(cam->angle);

    rx = x * c - y * s;
    ry = x * s + y * c;

    *wx = rx + cam->x;
    *wy = ry + cam->y;
}
