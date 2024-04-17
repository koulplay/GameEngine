#pragma once

#include "vertexBuffer.h"


namespace game_engine {
class IndexBuffer {
public:
    IndexBuffer(const void* data, const size_t count, const VertexBuffer::EUsage usage = VertexBuffer::EUsage::STATIC);
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&) = delete;

    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    void Bind() const;
    static void Unbind();
    [[nodiscard]] size_t GetCount() const { return count_; }

private:
    unsigned int id_ = 0;
    size_t count_;
};
} //end namespace game_engine
