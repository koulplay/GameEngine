#pragma once

#include "vertexBuffer.h"
#include "indexBuffer.h"

namespace game_engine {

class VertexArray {
public:

	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&) = delete;

	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;

	void AddVertexBuffer(const VertexBuffer& vertex_buffer);
	void AddIndexBuffer(const IndexBuffer& index_buffer);

	void Bind() const;
	static void Unbind();

	[[nodiscard]] size_t GetIndecesCount() const {return indeces_count_; }

private:
	unsigned int id_ = 0;
	unsigned int elements_count_ = 0;
	size_t indeces_count_ = 0;
};

} //end namespace game_engine