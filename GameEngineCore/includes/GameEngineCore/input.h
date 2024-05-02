#pragma once

#include "keys.h"

#include <cstddef>

namespace engine {

class Input {
public:
    static bool isKeyPressed(const KeyCode key_code);
    static void PressKey(const KeyCode key_code);
    static void ReleaseKey(const KeyCode key_code);

private:
    static bool keys_pressed_[static_cast<size_t>(KeyCode::KEY_LAST)];
};

} // end namespace engine
