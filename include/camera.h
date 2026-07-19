#ifndef INC_CAMERA_H
#define INC_CAMERA_H

#include <math/mat4.h>
#include <math/vec3.h>

typedef enum {
    CAMERA_FORWARD,
    CAMERA_BACKWARD,
    CAMERA_LEFT,
    CAMERA_RIGHT,
    CAMERA_UP,
    CAMERA_DOWN,
} CameraMove;

// Yaw / Pitch camera
typedef struct {
    // World position
    vec3 position;

    // Euler angles
    float yaw;
    float pitch;

    // Orthonormal basis of the camera
    vec3 forward;
    vec3 right;
    vec3 up;

    vec3 world_up;
} CameraTransform;

typedef struct {
    float fov;
    float aspect;
    float near_plane;
    float far_plane;
} CameraLens;

typedef struct {
    CameraLens lens;
    CameraTransform transform;
} Camera;

void camera_init(Camera* cam, vec3 pos, float yaw, float pitch, float aspect);

void camera_move(Camera* cam, CameraMove direction, float amount);
void camera_rotate(Camera* cam, float yaw_offset, float pitch_offset);

mat4 camera_view_matrix(const Camera* cam);
mat4 camera_projection_matrix(const Camera* cam);

#endif
