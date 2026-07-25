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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
        /*       positions   |        color      | texture coords */

        // FRONT FACE (+Z)
        -0.5f, -0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 0.0f, // 0 bottom left
         0.5f, -0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 0.0f, // 1 bottom right
         0.5f,  0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 1.0f, // 2 top right
        -0.5f,  0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 1.0f, // 3 top left

        // RIGHT FACE (+X)
         0.5f, -0.5f,  0.5f,   1.0f, 0.20f, 0.0f,   0.0f, 0.0f, // 4 bottom left
         0.5f, -0.5f, -0.5f,   1.0f, 0.20f, 0.0f,   1.0f, 0.0f, // 5 bottom right
         0.5f,  0.5f, -0.5f,   1.0f, 0.20f, 0.0f,   1.0f, 1.0f, // 6 top right
         0.5f,  0.5f,  0.5f,   1.0f, 0.20f, 0.0f,   0.0f, 1.0f, // 7 top left

        // BACK FACE (-Z)
         0.5f, -0.5f, -0.5f,   1.0f, 0.20f, 0.0f,   0.0f, 0.0f, // 8 bottom left
        -0.5f, -0.5f, -0.5f,   1.0f, 0.20f, 0.0f,   1.0f, 0.0f, // 9 bottom right
        -0.5f,  0.5f, -0.5f,   1.0f, 0.20f, 0.0f,   1.0f, 1.0f, // 10 top right
         0.5f,  0.5f, -0.5f,   1.0f, 0.20f, 0.0f,   0.0f, 1.0f, // 11 top left

        // LEFT FACE (-X)
        -0.5f, -0.5f, -0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 0.0f, // 12 bottom left
        -0.5f, -0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 0.0f, // 13 bottom right
        -0.5f,  0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 1.0f, // 14 top right
        -0.5f,  0.5f, -0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 1.0f, // 15 top left

        // TOP FACE (+Y)
        -0.5f,  0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 0.0f, // 16 bottom left
         0.5f,  0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 0.0f, // 17 bottom right
         0.5f,  0.5f, -0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 1.0f, // 18 top right
        -0.5f,  0.5f, -0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 1.0f, // 19 top left

        // BOTTOM FACE (-Y)
        -0.5f, -0.5f, -0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 0.0f, // 20 bottom left
         0.5f, -0.5f, -0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 0.0f, // 21 bottom right
         0.5f, -0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   1.0f, 1.0f, // 22 top right
        -0.5f, -0.5f,  0.5f,   1.0f, 0.75f, 0.0f,   0.0f, 1.0f  // 23 top left
    };

    GLuint indices[] = {
        // FRONT
        0, 1, 3,
        1, 2, 3,

        // RIGHT
        4, 5, 7,
        5, 6, 7,

        // BACK
        8, 9, 11,
        9, 10, 11,

        // LEFT
        12, 13, 15,
        13, 14, 15,

        // TOP
        16, 17, 19,
        17, 18, 19,

        // BOTTOM
        20, 21, 23,
        21, 22, 23
    };

    Mesh cube;
    mesh_init(&cube, vertices, sizeof(vertices), indices, sizeof(indices));

    return cube;
}
