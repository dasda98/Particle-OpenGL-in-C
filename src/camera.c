#include <camera/camera.h>
#include <cglm/cam.h>

#include <GLFW/glfw3.h>


void initCamera(Camera* camera, vec3 position) {
    glm_vec3_copy(position, camera->position);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, camera->front);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, camera->up);
    camera->yaw = -90.0f;
    camera->pitch = 0.0f;
    camera->speed = 2.5f;
    camera->sensitivity = 0.1f;
    camera->zoom = 45.0f;
}

void getViewMatrix(Camera* camera, mat4 view) {
    vec3 center;
    glm_vec3_add(camera->position, camera->front, center);
    glm_lookat(camera->position, center, camera->up, view);
}

void getProjectionMatrix(Camera* camera, mat4 projection, float aspectRatio) {
    glm_perspective(glm_rad(camera->zoom), aspectRatio, 0.1f, 100.0f, projection);
}

void processKeyboard(Camera* camera, int direction, float deltaTime) {
    float velocity = camera->speed * deltaTime;

    if (direction == GLFW_KEY_W) {
        vec3 temp;
        glm_vec3_scale(camera->front, velocity, temp);
        glm_vec3_add(camera->position, temp, camera->position);
    }

    if (direction == GLFW_KEY_S) {
        vec3 temp;
        glm_vec3_scale(camera->front, velocity, temp);
        glm_vec3_sub(camera->position, temp, camera->position);
    }

    if (direction == GLFW_KEY_A) {
        vec3 left;
        glm_vec3_cross(camera->front, camera->up, left);
        glm_vec3_normalize(left);
        glm_vec3_scale(left, velocity, left);
        glm_vec3_sub(camera->position, left, camera->position);
    }

    if (direction == GLFW_KEY_D) {
        vec3 right;
        glm_vec3_cross(camera->up, camera->front, right);
        glm_vec3_normalize(right);
        glm_vec3_scale(right, velocity, right);
        glm_vec3_sub(camera->position, right, camera->position);
    }
}

void processMouseMovement(Camera* camera, float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= camera->sensitivity;
    yoffset *= camera->sensitivity;

    camera->yaw += xoffset;
    camera->pitch += yoffset;

    if (constrainPitch) {
        if (camera->pitch > 89.0f)
            camera->pitch = 89.0f;
        if (camera->pitch < -89.0f)
            camera->pitch = -89.0f;
    }

    vec3 front;
    front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    front[1] = sin(glm_rad(camera->pitch));
    front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_normalize_to(front, camera->front);
}