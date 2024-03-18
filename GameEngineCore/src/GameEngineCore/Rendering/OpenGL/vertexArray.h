#pragma once

#include "vertexBuffer.h"

namespace game_engine {

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&) = delete;

	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;

	void AddBuffer(const VertexBuffer& vertex_buffer);
	void Bind() const;
	static void Unbind();

private:
	unsigned int id_ = 0;
	unsigned int elements_count_ = 0;
};

} //end namespace game_engine