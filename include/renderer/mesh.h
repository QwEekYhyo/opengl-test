#ifndef INC_MESH_H
#define INC_MESH_H

#include <glad/glad.h>

typedef struct {
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    unsigned int index_count;
} Mesh;

void mesh_init(Mesh* mesh,
               GLfloat* vertices, unsigned int vertex_count,
               GLuint* indices, unsigned int index_count);

void mesh_destroy(Mesh* mesh);

Mesh mesh_cube(void);

#endif
