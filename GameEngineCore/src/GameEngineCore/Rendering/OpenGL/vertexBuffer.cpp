#include "vertexBuffer.h"

#include "GameEngineCore/log.h"

#include <glad/glad.h>

namespace game_engine {

constexpr GLenum usageToGLenum(const VertexBuffer::EUsage usage) {
	switch(usage) {
		case VertexBuffer::EUsage::STATIC: return GL_STATIC_DRAW;
		case VertexBuffer::EUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
		case VertexBuffer::EUsage::STREAM: return GL_STREAM_DRAW;
	}

	LOG_ERROR("Unknown VertexBuffer usage");
	return GL_STREAM_DRAW;
}


VertexBuffer::VertexBuffer(const void* data, const size_t size, const EUsage usage) {
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, id_);
	glBufferData(GL_ARRAY_BUFFER, size, data, usageToGLenum(usage));
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id_);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	:id_(other.id_) {
	other.id_ = 0;
}
VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept {
	id_ = other.id_;
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