#include "indexBuffer.h"

#include "GameEngineCore/log.h"

#include <glad/glad.h>

namespace game_engine {
constexpr GLenum usageToGLenum(const VertexBuffer::EUsage usage) {
    switch (usage) {
        case VertexBuffer::EUsage::STATIC: return GL_STATIC_DRAW;
        case VertexBuffer::EUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
        case VertexBuffer::EUsage::STREAM: return GL_STREAM_DRAW;
    }

    LOG_ERROR("Unknown VertexBuffer usage");
    return GL_STREAM_DRAW;
}

IndexBuffer::IndexBuffer(const void* data, const size_t count, const VertexBuffer::EUsage usage)
    : count_(count) {
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, usageToGLenum(usage));
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id_);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : id_(other.id_)
    , count_(other.count_) {
    other.id_ = 0;
    other.count_ = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept {
    id_ = other.id_;
    count_ = other.count_;
    other.id_ = 0;
    other.count_ = 0;
    return *this;
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void IndexBuffer::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
} // game_engine
