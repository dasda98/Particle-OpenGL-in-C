#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct {
    vec3 position;
    vec3 front;
    vec3 up;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float zoom;
} Camera;

void initCamera(Camera* camera, vec3 position);
void getViewMatrix(Camera* camera, mat4 view);
void getProjectionMatrix(Camera* camera, mat4 projection, float aspectRatio);
void processKeyboard(Camera* camera, int direction, float deltaTime);
void processMouseMovement(Camera* camera, float xoffset, float yoffset, GLboolean constrainPitch);

#endif //CAMERA_H
