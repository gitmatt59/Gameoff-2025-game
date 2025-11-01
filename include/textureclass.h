#pragma once

#include <string>
#include <glad/glad.h> // for GLuint, GLenum, GL_TEXTURE_2D, etc.
#include <stb_image.h> // included normally -- no STB_IMAGE_IMPLEMENTATION here

class Texture {
public:
    GLuint ID = 0;
    int width = 0, height = 0, channels = 0;
    
    // take const std::string& or const char*
    Texture(const std::string& path) {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data) {
            // make error handler later :>
            return;
        }

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // choose correct format
        GLenum format = (channels == 4) ? GL_RGBA : (channels == 3 ? GL_RGB : GL_RED);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    void activate(GLenum number) const {
        glActiveTexture(number);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    ~Texture() {
        if (ID) {
            glDeleteTextures(1, &ID);
        }
    }
};
