#include "rendererOpenGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertexArray.h"
#include "GameEngineCore/log.h"

namespace engine {

std::string GLSourceToString(GLenum source) {
    switch (source) {
        case GL_DEBUG_SOURCE_API: return "GL_DEBUG_SOURCE_API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return  "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "GL_DEBUG_SOURCE_THIRD_PARTY";
        case GL_DEBUG_SOURCE_APPLICATION: return "GL_DEBUG_SOURCE_APPLICATION";
        case GL_DEBUG_SOURCE_OTHER: return "GL_DEBUG_SOURCE_OTHER";
        default: return "GL_DEBUG_SOURCE_UNKNOWN";
    }
}

std::string GLTypeToString(GLenum source) {
    switch (source) {
        case GL_DEBUG_TYPE_ERROR: return "GL_DEBUG_TYPE_ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY: return "GL_DEBUG_TYPE_PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE: return "GL_DEBUG_TYPE_PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER: return "GL_DEBUG_SOURCE_OTHER";
        case GL_DEBUG_TYPE_PUSH_GROUP: return "GL_DEBUG_SOURCE_OTHER";
        case GL_DEBUG_TYPE_POP_GROUP: return "GL_DEBUG_SOURCE_OTHER";
        case GL_DEBUG_TYPE_OTHER: return "GL_DEBUG_SOURCE_OTHER";
        default: return "GL_DEBUG_TYPE_UNKNOWN";
    }
}

bool RendererOpenGL::Init(GLFWwindow* p_window) {
    glfwMakeContextCurrent(p_window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        LOG_CRITICAL("Failed to initialize GLFW!");
        return false;
    }
    LOG_INFO("  OpenGL context initializer");
    LOG_INFO("  OpenGL Vender: {0}", GetVendorStr());
    LOG_INFO("  OpenGL Renderer: {0}", GetRendererStr());
    LOG_INFO("  OpenGL Version: {0}", GetVersionStr());

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION,0, nullptr, GL_FALSE);

    glDebugMessageCallback([](GLenum source,
                                       GLenum type,
                                       GLuint id,
                                       GLenum severity,
                                       GLsizei length,
                                       const GLchar *message,
                                       const void *userParam) {
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                LOG_CRITICAL("{0}, {1}, {2}, {3}", GLSourceToString(source), GLTypeToString(type), id, message);
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                LOG_ERROR("{0}, {1}, {2}, {3}", GLSourceToString(source), GLTypeToString(type), id, message);
                break;
            case GL_DEBUG_SEVERITY_LOW:
                LOG_WARN("{0}, {1}, {2}, {3}", GLSourceToString(source), GLTypeToString(type), id, message);
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                LOG_INFO("{0}, {1}, {2}, {3}", GLSourceToString(source), GLTypeToString(type), id, message);
                break;
        }
    }, nullptr);

    return true;
}

void RendererOpenGL::DrawElements(const VertexArray& vertex_array) {
    vertex_array.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_array.GetIndecesCount()), GL_UNSIGNED_INT, nullptr);
}

void RendererOpenGL::DrawArrays(const VertexArray& vertex_array, int count) {
    vertex_array.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void RendererOpenGL::SetClearColor(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void RendererOpenGL::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
