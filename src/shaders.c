#include <shaders.h>

#include <stdio.h>

int load_shader_source(const char* filename, char* buffer, long size) {
#if defined(_WIN32)
#error "Opening files on Windows has not yet been implemented"
#else
    FILE* file = fopen(filename, "r");
    if (!file)
        return -1;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size > size - 1) // -1 for \0 ?
        return -2;

    // Maybe check return value?
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Hopefully this is in bounds

    fclose(file);
#endif

    return 0;
}

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

int create_shader_program(GLuint* shader_program) {
    int error;

    char source_buffer[512];
    const GLchar* shader_source = source_buffer;

    error = load_shader_source(
            "assets/shaders/default.vert",
            source_buffer,
            sizeof(source_buffer));
    if (error) {
        perror("Could not load vertex shader source");
        return error;
    }

    GLuint vertex_shader;
    error = compile_shader(&shader_source, GL_VERTEX_SHADER, &vertex_shader);
    if (error)
        return error;

    error = load_shader_source(
            "assets/shaders/default.frag",
            source_buffer,
            sizeof(source_buffer));
    if (error) {
        glDeleteShader(vertex_shader);
        perror("Could not load fragment shader source");
        return error;
    }

    GLuint fragment_shader;
    error = compile_shader(&shader_source, GL_FRAGMENT_SHADER, &fragment_shader);
    if (error) {
        glDeleteShader(vertex_shader);
        return error;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint link_success;
    glGetProgramiv(program, GL_LINK_STATUS, &link_success);
    if (!link_success) {
        GLchar info_log[512];
        glGetProgramInfoLog(program, sizeof(info_log), NULL, info_log);
        printf("Error while linking shader program: %s\n", info_log);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return -1;
    }

    // Don't need them anymore
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    *shader_program = program;
    return 0;
}
