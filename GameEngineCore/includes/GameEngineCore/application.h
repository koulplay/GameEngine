#pragma once

#include <GameEngineCore/windowEvent.h>
#include <GameEngineCore/keyEvent.h>
#include <GameEngineCore/mouseEvent.h>
#include <GameEngineCore/camera.h>

#include <memory>

namespace engine {

class Application {
public:
    Application();
    virtual ~Application();

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    virtual int Start(unsigned int window_wight, unsigned int window_height, const char* title);

    virtual void OnUpdate() {}
    virtual void OnUIDraw() {}

    void OnEvent(EventBase& event);
    bool OnWindowClose(EventWindowClose& event);

    bool perspective_camera = true;
    Camera camera;

private:
    bool close_window_ = false;
    std::unique_ptr<class Window> p_window_;
};

} // end namespace engine