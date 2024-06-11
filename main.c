#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <GLFW/glfw3.h>


#include <shader/shader.h>
#include <particle/particle_system.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;


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

    // Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD!\n");
        return -1;
    }

    Shader myShader = createShader("../shaders/shader.vert", "../shaders/shader.frag");

    ParticleSystem ps;
    initParticleSystem(&ps);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // DeltaTime
        float currentFrame = glfwGetTime();
        static float lastFrame = 0.0f;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);
        updateParticles(&ps, deltaTime);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

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
}
