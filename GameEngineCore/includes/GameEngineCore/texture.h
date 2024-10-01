#pragma once

namespace engine {

class Texture {
public:
    Texture(const char* texture_path);
    ~Texture();

    Texture() = delete;
    Texture(const Texture&) = delete;
    Texture& operator=(Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void SetActiveTexture(int texture_block);

    void Bind();
    void Unbind();

private:
    unsigned int id_ = 0;

    unsigned char* image_;
    int width_;
    int height_;
};

}// end namespace engine
