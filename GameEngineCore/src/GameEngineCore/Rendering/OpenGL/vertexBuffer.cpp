#include "vertexBuffer.h"

#include "GameEngineCore/log.h"

#include <glad/glad.h>

#include <cstddef>
#include <utility>

namespace game_engine {
constexpr unsigned int ShaderDataTypeToComponentsCount(const ShaderDataType type) {
    switch (type) {
        case ShaderDataType::FLOAT:
        case ShaderDataType::INT:
            return 1;
        case ShaderDataType::FLOAT2:
        case ShaderDataType::INT2:
            return 2;
        case ShaderDataType::FLOAT3:
        case ShaderDataType::INT3:
            return 3;
        case ShaderDataType::FLOAT4:
        case ShaderDataType::INT4:
            return 4;
    }
    LOG_ERROR("ShaderDataTypeToComponentsCount: unknown ShaderDataType");
    return 0;
}

constexpr unsigned int ShaderDataTypeSize(const ShaderDataType type) {
    switch (type) {
        case ShaderDataType::FLOAT:
        case ShaderDataType::FLOAT2:
        case ShaderDataType::FLOAT3:
        case ShaderDataType::FLOAT4:
            return sizeof(GLfloat) * ShaderDataTypeToComponentsCount(type);
        case ShaderDataType::INT:
        case ShaderDataType::INT2:
        case ShaderDataType::INT3:
        case ShaderDataType::INT4:
            return sizeof(GLint) * ShaderDataTypeToComponentsCount(type);
    }
    LOG_ERROR("ShaderDataTypeSize: unknown ShaderDataType");
    return 0;
}

constexpr unsigned int ShaderDataTypeToComponentType(const ShaderDataType type) {
    switch (type) {
        case ShaderDataType::FLOAT:
        case ShaderDataType::FLOAT2:
        case ShaderDataType::FLOAT3:
        case ShaderDataType::FLOAT4:
            return GL_FLOAT;
        case ShaderDataType::INT:
        case ShaderDataType::INT2:
        case ShaderDataType::INT3:
        case ShaderDataType::INT4:
            return GL_INT;
    }
    LOG_ERROR("ShaderDataTypeSize: unknown ShaderDataType");
    return 0;
}

constexpr GLenum usageToGLenum(const VertexBuffer::EUsage usage) {
    switch (usage) {
        case VertexBuffer::EUsage::STATIC: return GL_STATIC_DRAW;
        case VertexBuffer::EUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
        case VertexBuffer::EUsage::STREAM: return GL_STREAM_DRAW;
    }

    LOG_ERROR("Unknown VertexBuffer usage");
    return GL_STREAM_DRAW;
}


BufferElement::BufferElement(const ShaderDataType type)
    : type(type)
    , component_type(ShaderDataTypeToComponentType(type))
    , components_count(ShaderDataTypeToComponentsCount(type))
    , size(ShaderDataTypeSize(type))
    , offset(0) {
}

VertexBuffer::VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const EUsage usage)
    : buffer_layout_(std::move(buffer_layout)) {
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, data, usageToGLenum(usage));
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id_);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : id_(other.id_)
    , buffer_layout_(std::move(other.buffer_layout_)) {
    other.id_ = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
    id_ = other.id_;
    buffer_layout_ = std::move(other.buffer_layout_);
    other.id_ = 0;
    return *this;
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
} //end namespace game_engine
