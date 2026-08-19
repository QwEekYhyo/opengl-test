#ifndef INC_TEXTURE_H
#define INC_TEXTURE_H

#include <glad/glad.h>

typedef struct {
    GLuint object_name;
} Texture;

int generate_texture(Texture* texture, const char* filename);

void texture_destroy(Texture* texture);

#endif
