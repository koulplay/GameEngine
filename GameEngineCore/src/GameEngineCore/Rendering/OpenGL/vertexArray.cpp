#include "vertexArray.h"
#include "vertexBuffer.h"

#include "GameEngineCore/log.h"

#include <glad/glad.h>

namespace engine {



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

void VertexArray::AddVertexBuffer(const VertexBuffer& vertex_buffer) {
	Bind();
	vertex_buffer.Bind();

	for (const BufferElement& current_element : vertex_buffer.GetLayout().GetElement()) {
		glVertexAttribPointer(
			elements_count_,
			static_cast<GLint>(current_element.components_count),
			current_element.component_type,
			GL_FALSE,
			static_cast<GLsizei>(vertex_buffer.GetLayout().GetStride()),
			reinterpret_cast<const void*>(current_element.offset));
		glEnableVertexAttribArray(elements_count_);
		++elements_count_;
	}
}

void VertexArray::AddIndexBuffer(const IndexBuffer& index_buffer) {
	Bind();
	index_buffer.Bind();

	indeces_count_ = index_buffer.GetCount();

}

void VertexArray::Bind() const {
	glBindVertexArray(id_);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}

} //end namespace engine