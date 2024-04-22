#pragma once

#include <glm/mat4x4.hpp>

namespace engine {

class ShaderProgram{
public:
	ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
	~ShaderProgram();


	ShaderProgram() = delete;
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(ShaderProgram&) = delete;

	ShaderProgram(ShaderProgram&& other) noexcept;
	ShaderProgram& operator=(ShaderProgram&& other) noexcept;

	void Bind() const;
	static void Unbind();
	[[nodiscard]] bool IsCompiled() const { return is_compiled_; }

	void SetMatrix4(const char* name, const glm::mat4& matrix) const;

private:
	bool is_compiled_ = false;
	unsigned int id_ = 0;
};

} //end namespace engine