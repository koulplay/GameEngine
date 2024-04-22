#include "rendererOpenGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertexArray.h"
#include "GameEngineCore/log.h"

namespace engine {
bool RendererOpenGL::Init(GLFWwindow* p_window) {
    glfwMakeContextCurrent(p_window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        LOG_CRITICAL("Failed to initialize GLFW!");
        return false;
    }
    LOG_INFO("OpenGL context initializer");
    LOG_INFO("  Vender: {0}", GetVendorStr());
    LOG_INFO("  Renderer: {0}", GetRendererStr());
    LOG_INFO("  Version: {0}", GetVersionStr());

    return true;
}

void RendererOpenGL::Draw(const VertexArray& vertex_array) {
    vertex_array.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_array.GetIndecesCount()), GL_UNSIGNED_INT, nullptr);
}

void RendererOpenGL::SetClearColor(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void RendererOpenGL::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererOpenGL::SetViewport(const unsigned int width, const unsigned int height,
                                 const unsigned int left_offset, const unsigned int bottom_offset) {
    glViewport(left_offset, bottom_offset, width, height);
}

const char* RendererOpenGL::GetVendorStr() {
    return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

const char* RendererOpenGL::GetRendererStr() {
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

const char* RendererOpenGL::GetVersionStr() {
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}
} // end namespace engine
