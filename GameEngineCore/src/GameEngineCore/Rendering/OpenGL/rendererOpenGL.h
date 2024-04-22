#pragma once

struct GLFWwindow;

namespace engine {
class VertexArray;

class RendererOpenGL {
public:
    static bool Init(GLFWwindow* p_window);

    static void Draw(const VertexArray& vertex_array);
    static void SetClearColor(const float r, const float g, const float b, const float a);
    static void Clear();
    static void SetViewport(const unsigned int width, const unsigned int height,
                            const unsigned int left_offset = 0, const unsigned int bottom_offset = 0);

    static const char* GetVendorStr();
    static const char* GetRendererStr();
    static const char* GetVersionStr();
};
}; // end namespace engine
