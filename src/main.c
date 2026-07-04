#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include <shaders.h>

// Maybe I should use glfwGetWindowSize instead of keeping track of this?
int window_width = 1280;
int window_height = 720;

void window_size_func(GLFWwindow* window, int width, int height) {
    (void)window;

    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

int main(void) {
    int error_code = 0;

    if (!glfwInit()) {
        perror("Failed to initialize GLFW library");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Epic Gamer Moment", NULL, NULL);

    if (!window) {
        perror("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to load OpenGL functions");
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, window_size_func);

    /********** Shaders compiling **********/
    GLuint shader_program;
    error_code = create_shader_program(&shader_program);
    if (error_code)
        goto done;

    /********** Create and bind vertex buffer and vertex array **********/
    GLfloat vertices[] = {
        -0.2f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.2f, 0.0f, 0.0f,
        -0.1f, 0.2f, 0.0f,
        0.1f, 0.2f, 0.0f,
        0.0f, 0.4f, 0.0f,
    };
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 4,
        3, 4, 5,
    };

    GLuint vbo, vao, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        // TODO: process input

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

done:
    printf("Exiting Epic Gamer Moment...\n");
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return error_code;
}
