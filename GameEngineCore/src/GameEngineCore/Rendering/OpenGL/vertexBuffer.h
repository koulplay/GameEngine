#pragma once
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace engine {
enum class ShaderDataType {
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    INT,
    INT2,
    INT3,
    INT4,
};

struct BufferElement {
    ShaderDataType type;
    uint32_t component_type;
    size_t components_count;
    size_t size;
    size_t offset;

    BufferElement(const ShaderDataType type);
};

class BufferLayout {
public:
    BufferLayout(std::initializer_list<BufferElement> elements)
        : elements_(elements) {
        size_t offset = 0;
        stride_ = 0;
        for (auto& element : elements_) {
            element.offset = offset;
            offset += element.size;
            stride_ += element.size;
        }
    }

    [[nodiscard]] const std::vector<BufferElement>& GetElement() const { return elements_; }
    [[nodiscard]] size_t GetStride() const { return stride_; }

private:
    std::vector<BufferElement> elements_;
    size_t stride_ = 0;
};

class VertexBuffer {
public:
    enum class EUsage {
        STATIC,
        DYNAMIC,
        STREAM
    };

    VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout,
                 const EUsage usage = VertexBuffer::EUsage::STATIC);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void Bind() const;
    static void Unbind();

    [[nodiscard]] const BufferLayout& GetLayout() const { return buffer_layout_; }

private:
    unsigned int id_ = 0;
    BufferLayout buffer_layout_;
};
} //end namespace engine
