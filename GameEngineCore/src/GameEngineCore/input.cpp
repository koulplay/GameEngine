#include "GameEngineCore/input.h"

namespace engine {

bool Input::keys_pressed_[static_cast<size_t>(KeyCode::KEY_LAST)] = {};

bool Input::isKeyPressed(const KeyCode key_code) {
    return keys_pressed_[static_cast<size_t>(key_code)];
}

void Input::PressKey(const KeyCode key_code) {
    keys_pressed_[static_cast<size_t>(key_code)] = true;
}

void Input::ReleaseKey(const KeyCode key_code) {
    keys_pressed_[static_cast<size_t>(key_code)] = false;
}
} // end namespace engine