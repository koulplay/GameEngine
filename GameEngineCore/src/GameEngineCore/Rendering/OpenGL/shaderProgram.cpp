#include "shaderProgram.h"

#include <GameEngineCore/log.h>
#include <glad/glad.h>

#include "glm/gtc/type_ptr.hpp"

namespace engine {

bool CreateShader(const char* source, const GLenum shader_type, GLuint& shader_id) {
    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &source, nullptr);
    glCompileShader(shader_id);

    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        char info_log[1024];
        glGetShaderInfoLog(shader_id, sizeof(info_log), nullptr, info_log);

        LOG_CRITICAL("Shader compilation error:\n{0}", info_log);
        return false;
    }
    return true;
}

ShaderProgram::ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src) {
    GLuint vertex_shader_id = 0;
    if (!CreateShader(vertex_shader_src, GL_VERTEX_SHADER, vertex_shader_id)) {
        LOG_CRITICAL("VERTEX SHADER: compile-time error");
        glDeleteShader(vertex_shader_id);
        return;
    }

    GLuint fragment_shader_id = 0;
    if (!CreateShader(fragment_shader_src, GL_FRAGMENT_SHADER, fragment_shader_id)) {
        LOG_CRITICAL("FRAGMENT SHADER: compile-time error");
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
        return;
    }

    id_ = glCreateProgram();
    glAttachShader(id_, vertex_shader_id);
    glAttachShader(id_, fragment_shader_id);
    glLinkProgram(id_);

    GLint success;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        char info_log[1024];
        glGetProgramInfoLog(id_, sizeof(info_log), nullptr, info_log);
        LOG_CRITICAL("SHADER PROGRAM Link-time error:\n{0}", info_log);
        glDeleteProgram(id_);
        id_ = 0;
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
        return;
    }
    is_compiled_ = true;

    glDetachShader(id_, vertex_shader_id);
    glDetachShader(id_, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
    id_ = other.id_;
    is_compiled_ = other.is_compiled_;

    other.id_ = 0;
    other.is_compiled_ = false;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
    glDeleteProgram(id_);
    id_ = other.id_;
    is_compiled_ = other.is_compiled_;

    other.id_ = 0;
    other.is_compiled_ = false;
    return *this;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id_);
}

void ShaderProgram::Bind() const {
    glUseProgram(id_);
}

void ShaderProgram::Unbind() {
    glUseProgram(0);
}

void ShaderProgram::SetMatrix4(const char* name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

} //end namespace engine
