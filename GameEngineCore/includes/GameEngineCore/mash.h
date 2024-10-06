#pragma once
#include "GameEngineCore/Rendering/OpenGL/shaderProgram.h"

#include <glm/glm.hpp>;
#include <string>;
#include <vector>;

namespace engine {
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(engine::ShaderProgram shader);

private:
    unsigned int VAO_, VBO_, EBO_;

    void setupMesh();
};

}// end namespace engine