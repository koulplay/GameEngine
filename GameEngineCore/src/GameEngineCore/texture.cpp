#include "GameEngineCore/texture.h"

#include <SOIL2.h>
#include <utility>

#include "glad/glad.h"

namespace engine {

Texture::Texture(const char* texture_path) {
    image_ = SOIL_load_image(texture_path, &width_, &height_, 0, SOIL_LOAD_RGB);

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image_);
}

Texture::~Texture() {
    Unbind();
}

Texture::Texture(Texture&& other) noexcept {
    id_ = other.id_;
    other.id_ = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    id_ = other.id_;
    other.id_ = 0;
    return *this;
}

void Texture::SetActiveTexture(const int texture_block) {
    glActiveTexture(texture_block);
    Bind();
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

}// end namespace engine