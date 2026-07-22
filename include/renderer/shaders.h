#ifndef INC_SHADERS_H
#define INC_SHADERS_H

#include <glad/glad.h> // This is only for typedefs

int load_shader_source(const char* filename, char* buffer, long size);
int compile_shader(const GLchar** source, GLenum type, GLuint* shader_res);

int create_shader_program(GLuint* shader_program);

#endif
