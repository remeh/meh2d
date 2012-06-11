#include <iostream>
#include "core/keyboardhandler.h"

namespace meh {

KeyboardHandler::KeyboardHandler() {
}

KeyboardHandler::~KeyboardHandler() {
}

void KeyboardHandler::refreshState() {
    al_get_keyboard_state(&state);
}

bool KeyboardHandler::keydown(int keycode) {
    return al_key_down(&state,keycode);
}

}
