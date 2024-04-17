#pragma once

namespace game_engine {

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

private:
	bool is_compiled_ = false;
	unsigned int id_ = 0;
};

} //end namespace game_engine