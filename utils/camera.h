#ifndef CAMERA_H
#define CAMERA_H

#include "hlinalg.h"

typedef struct Camera {
    Vec origin;
    Vec direction;
    float start;
    float end;
    int fov; // measured in degrees
} Camera;

#endif // CAMERA_H