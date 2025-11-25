#ifndef CAMERA2D_H
#define CAMERA2D_H

typedef struct {
    float x;
    float y;
    float zoom;
    float angle;
    float halfW;
    float halfH;
} Camera2D;

/* Public API */
void Camera2D_Init(Camera2D* cam, float x, float y, float viewW, float viewH);
void Camera2D_Move(Camera2D* cam, float dx, float dy);
void Camera2D_SetPosition(Camera2D* cam, float x, float y);
void Camera2D_SetZoom(Camera2D* cam, float zoom);
void Camera2D_SetAngle(Camera2D* cam, float angle);

void Camera2D_WorldToScreen(Camera2D* cam, float wx, float wy, float* sx, float* sy);
void Camera2D_ScreenToWorld(Camera2D* cam, float sx, float sy, float* wx, float* wy);

#endif
