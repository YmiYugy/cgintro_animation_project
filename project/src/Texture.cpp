
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


std::shared_ptr<Texture> TextureLoader::load(const std::filesystem::path &path) {
    int width, height, nrChannels;
    width = 0;
    height = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.generic_string().c_str(), &width, &height, &nrChannels, STBI_rgb);
    if (!data) {
        throw std::runtime_error("failed to load " + path.generic_string());
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    return std::make_shared<Texture>(Texture{
            .texture = texture,
            .width = width,
            .height = height
    });
}

std::shared_ptr<Texture> DepthTextureLoader::load(GLuint width, GLuint height) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    auto color = glm::vec4(1.0);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(color));

    return std::make_shared<Texture>(Texture{
            .texture = texture,
            .width = static_cast<int>(width),
            .height = static_cast<int>(height)
    });
}
