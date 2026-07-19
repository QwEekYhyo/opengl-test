#include <camera.h>

#include <math.h>

#include <math/mat4.h>
#include <math/my_math.h>
#include <math/vec3.h>

static void _camera_update_vectors(Camera* cam);

void camera_init(Camera* cam, vec3 pos, float yaw, float pitch, float aspect) {
    CameraLens* l = &cam->lens;
    CameraTransform* t = &cam->transform;

    l->aspect = aspect;

    // This is fixed here for now
    l->fov = 45.0f;
    l->near_plane = 0.1f;
    l->far_plane = 100.0f;

    t->position = pos;
    t->yaw = yaw;
    t->pitch = pitch;

    // This is fixed here for now
    t->world_up.x = 0.0f;
    t->world_up.y = 1.0f;
    t->world_up.z = 0.0f;

    _camera_update_vectors(cam);
}

void camera_move(Camera* cam, CameraMove direction, float amount) {
    CameraTransform* t = &cam->transform;

    switch (direction) {
    case CAMERA_FORWARD:
        t->position.x += amount * t->forward.x;
        t->position.y += amount * t->forward.y;
        t->position.z += amount * t->forward.z;
        break;
    case CAMERA_BACKWARD:
        t->position.x -= amount * t->forward.x;
        t->position.y -= amount * t->forward.y;
        t->position.z -= amount * t->forward.z;
        break;
    case CAMERA_RIGHT:
        t->position.x += amount * t->right.x;
        t->position.y += amount * t->right.y;
        t->position.z += amount * t->right.z;
        break;
    case CAMERA_LEFT:
        t->position.x -= amount * t->right.x;
        t->position.y -= amount * t->right.y;
        t->position.z -= amount * t->right.z;
        break;
    default: break;
    }
}

mat4 camera_view_matrix(const Camera* cam) {
    const CameraTransform* t = &cam->transform;

    return (mat4){ .buf = {
        t->right.x, t->up.x, -t->forward.x, 0.0f,
        t->right.y, t->up.y, -t->forward.y, 0.0f,
        t->right.z, t->up.z, -t->forward.z, 0.0f,
       -vec3_dot(t->right, t->position),
       -vec3_dot(t->up, t->position),
        vec3_dot(t->forward, t->position),
        1.0f
    } };
}

mat4 camera_projection_matrix(const Camera* cam) {
    return mat4_perspective(
            RADIANS(cam->lens.fov),
            cam->lens.aspect,
            cam->lens.near_plane,
            cam->lens.far_plane);
}

static void _camera_update_vectors(Camera* cam) {
    CameraTransform* t = &cam->transform;

    float y = RADIANS(t->yaw);
    float p = RADIANS(t->pitch);

    t->forward.x = cosf(y) * cosf(p);
    t->forward.y = sinf(p);
    t->forward.z = sinf(y) * cosf(p);

    t->forward = vec3_normalize(t->forward);

    // Use world_up to compute right vector
    t->right = vec3_normalize(vec3_cross(t->forward, t->world_up));
    // Use right to compute the camera up
    t->up = vec3_normalize(vec3_cross(t->right, t->forward));
}
