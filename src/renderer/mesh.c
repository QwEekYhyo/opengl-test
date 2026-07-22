#include <renderer/mesh.h>

void mesh_init(Mesh* mesh,
               GLfloat* vertices, unsigned int vertex_count,
               GLuint* indices, unsigned int index_count) {
    glGenBuffers(1, &mesh->vbo);
    glGenBuffers(1, &mesh->ebo);
    glGenVertexArrays(1, &mesh->vao);
    mesh->index_count = index_count;

    glBindVertexArray(mesh->vao);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count, indices, GL_STATIC_DRAW);

    // Maybe there is a way to automate the code bellow
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mesh_destroy(Mesh* mesh) {
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteBuffers(1, &mesh->ebo);
    // Maybe set all fields to 0?
}

Mesh mesh_cube(void) {
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

    Mesh cube;
    mesh_init(&cube, vertices, sizeof(vertices), indices, sizeof(indices));

    return cube;
}
