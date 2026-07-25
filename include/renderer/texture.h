#ifndef INC_TEXTURE_H
#define INC_TEXTURE_H

#include <glad/glad.h>

typedef struct {
    GLuint texture;
} Texture;

int generate_texture(Texture* texture, const char* filename);

#endif
