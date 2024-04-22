#pragma once

struct GLFWwindow;

namespace engine {

class UIModule {
public:
    static void OnWindowCreate(GLFWwindow* p_window);
    static void OnWindowClose();
    static void OnUIDrawBegin();
    static void OnUIDrawEnd();

    static void ShowExampleAppDockSpace(bool* p_open);
};

} // end namespace engine