#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include <camera.h>
#include <math/my_math.h>
#include <shaders.h>

#define CAMERA_SPEED 3.0f
#define CAMERA_SENSITIVITY 0.1f

// Maybe I should use glfwGetWindowSize instead of keeping track of this?
int window_width = 1280;
int window_height = 720;

// I really need a cleaner way to pass shit around in callbacks
Camera cam;
double last_frame = 0;
double dt = 0;

double cursor_posx;
double cursor_posy;

static void window_size_func(GLFWwindow* window, int width, int height) {
    (void)window;

    glViewport(0, 0, width, height);

    window_width = width;
    window_height = height;

    cam.lens.aspect = (float)width / height;
}

static void key_func(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;

    static unsigned char wireframe_enabled = 0;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    static unsigned char h_rebounce = 0;
    if (key == GLFW_KEY_H && action == GLFW_PRESS && !h_rebounce) {
        glPolygonMode(
                GL_FRONT_AND_BACK,
                wireframe_enabled ? GL_FILL : GL_LINE);
        wireframe_enabled = ~wireframe_enabled;
        h_rebounce = ~h_rebounce;
    }
    if (key == GLFW_KEY_H && action == GLFW_RELEASE && h_rebounce)
        h_rebounce = ~h_rebounce;
}

// This feels so stupid
static void poll_inputs(GLFWwindow* window) {
    if (
            glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS
            && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE
       )
        camera_move(&cam, CAMERA_FORWARD, CAMERA_SPEED * dt);

    if (
            glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS
            && glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE
       )
        camera_move(&cam, CAMERA_BACKWARD, CAMERA_SPEED * dt);

    if (
            glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
            && glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE
       )
        camera_move(&cam, CAMERA_RIGHT, CAMERA_SPEED * dt);

    if (
            glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
            && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE
       )
        camera_move(&cam, CAMERA_LEFT, CAMERA_SPEED * dt);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    (void)window;

    camera_rotate(
            &cam,
            CAMERA_SENSITIVITY * (xpos - cursor_posx),
            -CAMERA_SENSITIVITY * (ypos - cursor_posy));

    cursor_posx = xpos;
    cursor_posy = ypos;
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwGetCursorPos(window, &cursor_posx, &cursor_posy);

    camera_init(
            &cam,
            (vec3){ 0.0f, 0.0f, 3.0f },
            -90.0f, 0.0f,
            (float)window_width / window_height);

    glfwSetWindowSizeCallback(window, window_size_func);
    glfwSetKeyCallback(window, key_func);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    /********** Shaders compiling **********/
    GLuint shader_program;
    error_code = create_shader_program(&shader_program);
    if (error_code)
        goto done;

    /********** Create and bind vertex buffer and vertex array **********/
    GLfloat vertices[] = {
    /*       positions   |        color       */
        -0.5f, -0.5f, 0.5f, 1.0f, 0.75f, 0.0f, // bottom left
        0.5f, -0.5f, 0.5f, 1.0f, 0.75f, 0.0f, // bottom right
        0.5f, 0.5f, 0.5f, 1.0f, 0.75f, 0.0f, // top right
        -0.5f, 0.5f, 0.5f, 1.0f, 0.75F, 0.0f, // top left

        0.5f, -0.5f, -0.5f, 1.0f, 0.2f, 0.0f, // bottom right but behind
        0.5f, 0.5f, -0.5f, 1.0f, 0.2f, 0.0f, // top right but behind
                                             //
        -0.5f, -0.5f, -0.5f, 1.0f, 0.2f, 0.0f, // bottom left but behind
        -0.5f, 0.5f, -0.5f, 1.0f, 0.2f, 0.0f, // top left but behind
    };
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3,

        1, 2, 4,
        4, 5, 2,

        0, 3, 6,
        6, 7, 3,

        4, 5, 6,
        6, 7, 5,

        0, 1, 4,
        4, 6, 0,

        2, 3, 5,
        5, 7, 3,
    };

    // """World"""
    vec3 cube_positions[] = {
        { 3.0f, 2.0f, -5.0f },
        { -2.0f, 0.0f, -2.0f },
        { 0.0f, -2.0f, -10.0f },
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        double current_frame = glfwGetTime();
        dt = current_frame - last_frame;
        last_frame = current_frame;

        poll_inputs(window);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLint model_loc = glGetUniformLocation(shader_program, "model");
        GLint view_loc = glGetUniformLocation(shader_program, "view");
        GLint projection_loc = glGetUniformLocation(shader_program, "projection");

        glUseProgram(shader_program);

        mat4 view = camera_view_matrix(&cam);
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(view));
        mat4 projection = camera_projection_matrix(&cam);
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, value_ptr(projection));

        glBindVertexArray(vao);

        for (unsigned int i = 0; i < sizeof(cube_positions) / sizeof(vec3); i++) {
            mat4 model = mat4_translate(cube_positions[i]);
            model = mat4_mul(
                    model,
                    mat4_rotate_y(current_frame * (1.0f+i)));
            model = mat4_mul(
                    model,
                    mat4_rotate_x(current_frame * (1.0f+i)));

            glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(model));

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

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
