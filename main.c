#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

// OMG we got code-ception
const GLchar* vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main() {\n"
    "gl_Position = vec4(pos, 1.0f);\n"
    "}";

const GLchar* fragment_shader_source =
    "#version 330 core\n"
    "out vec4 frag_color;\n"
    "void main() {\n"
    "frag_color = vec4(0.75f, 0.0f, 0.5f, 1.0f);\n"
    "}";

int compile_shader(const GLchar** source, GLenum type, GLuint* shader_res) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, source, NULL);
    glCompileShader(shader);

    if (shader_res)
        *shader_res = shader;

    GLint compile_success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_success);

    if (!compile_success) {
        GLchar info_log[512];
        glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
        printf("Error while compiling shader: %s\n", info_log);
        return -1;
    }

    return 0;
}

int main(void) {
    int error_code = 0;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // For Mac OS apparently
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Epic Gamer Moment", NULL, NULL);

    if (!window) {
        perror("Failed to create GLFW window");
        error_code = -1;
        goto done;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize GLAD");
        error_code = -1;
        goto done;
    }

    glViewport(0, 0, 1280, 720);
    // TODO: set frame buffer size callback

    /********** Shaders compiling **********/
    GLuint vertex_shader;
    error_code = compile_shader(&vertex_shader_source, GL_VERTEX_SHADER, &vertex_shader);
    if (error_code)
        goto done;

    GLuint fragment_shader;
    error_code = compile_shader(&fragment_shader_source, GL_FRAGMENT_SHADER, &fragment_shader);
    if (error_code)
        goto done;

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    GLint link_success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &link_success);
    if (!link_success) {
        GLchar info_log[512];
        glGetProgramInfoLog(shader_program, sizeof(info_log), NULL, info_log);
        printf("Error while linking shader program: %s\n", info_log);

        error_code = -1;
        goto done;
    }

    // Don't need them anymore
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    /********** Create and bind vertex buffer and vertex array **********/
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint vb, va;
    glGenBuffers(1, &vb);
    glGenVertexArrays(1, &va);

    glBindVertexArray(va);

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
        glBindVertexArray(va);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

done:
    printf("Exiting Epic Gamer Moment...\n");
    glDeleteVertexArrays(1, &va);
    glDeleteBuffers(1, &vb);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return error_code;
}
