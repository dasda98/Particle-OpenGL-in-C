#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

#include <shader/shader.h>
#include <particle/particle_system.h>
#include <camera/camera.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

// Settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// Camera
Camera camera;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main(void) {

    srand(time(NULL));

    // GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD!\n");
        return -1;
    }

    // OpenGL global states
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    // Initialize shader
    Shader myShader = createShader("../shaders/shader.vert", "../shaders/shader.frag");

    // Initialize Camera
    vec3 cameraPos = {0.0f, 0.0f, 3.0f};
    initCamera(&camera, cameraPos);

    mat4 view, projection, model;

    glm_mat4_identity(model);

    // Initialize Particle System
    ParticleSystem ps;
    initParticleSystem(&ps);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // DeltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Update
        glClear(GL_COLOR_BUFFER_BIT);
        updateParticles(&ps, deltaTime);

        getViewMatrix(&camera, view);
        getProjectionMatrix(&camera, projection, (float)(WIDTH/HEIGHT));

        GLuint viewLoc = glGetUniformLocation(myShader.ID, "view");
        GLuint projectionLoc = glGetUniformLocation(myShader.ID, "projection");
        GLuint modelLoc = glGetUniformLocation(myShader.ID, "model");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)view);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float*)projection);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)model);

        // Render
        useShader(&myShader);
        renderParticles(&ps);

        // GLFW events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    deleteParticleSystem(&ps);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        processKeyboard(&camera, GLFW_KEY_W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        processKeyboard(&camera, GLFW_KEY_S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        processKeyboard(&camera, GLFW_KEY_A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        processKeyboard(&camera, GLFW_KEY_D, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = (float) xposIn;
    float ypos = (float) yposIn;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    processMouseMovement(&camera, xoffset, yoffset, true);
}