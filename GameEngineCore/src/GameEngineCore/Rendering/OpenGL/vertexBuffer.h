#pragma once

namespace game_engine {

class VertexBuffer {
public:
	enum class EUsage{
		STATIC,
		DYNAMIC,
		STREAM
	};

	VertexBuffer(const void* data, const size_t size, const EUsage usage = VertexBuffer::EUsage::STATIC);
	~VertexBuffer();

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(VertexBuffer&) = delete;

	VertexBuffer(VertexBuffer&& other) noexcept;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;

	void Bind() const;
	static void Unbind();

private:
	unsigned int id_ = 0;
};

} //end namespace game_engine