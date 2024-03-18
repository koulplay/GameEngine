#include "vertexArray.h"
#include "vertexBuffer.h"

#include "GameEngineCore/log.h"

#include <glad/glad.h>

namespace game_engine {



VertexArray::VertexArray() {
	glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &id_);
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	: id_(other.id_)
	, elements_count_(other.elements_count_){
	other.id_ = 0;
	other.elements_count_ = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
	id_ = other.id_;
	elements_count_ = other.elements_count_;
	other.id_ = 0;
	other.elements_count_ = 0;
	return *this;
}

void VertexArray::AddBuffer(const VertexBuffer& vertex_buffer) {
	Bind();
	vertex_buffer.Bind();
	glEnableVertexAttribArray(elements_count_);
	glVertexAttribPointer(elements_count_, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	++elements_count_;
}

void VertexArray::Bind() const {
	glBindVertexArray(id_);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}

} //end namespace game_engine