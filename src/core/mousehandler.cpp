#include "core/mousehandler.h"
#include "core/vector2d.h"

namespace meh {

MouseHandler::MouseHandler() {

}

MouseHandler::~MouseHandler() {

}

void MouseHandler::refreshState() {
    al_get_mouse_state(&state);
}

bool MouseHandler::left() {
    return state.buttons & 1;
}

bool MouseHandler::middle() {
    return state.buttons & 4;
}

bool MouseHandler::right() {
    return state.buttons & 2;
}

int MouseHandler::wheel() {
    return state.z;
}

Vector2d<float> MouseHandler::position() {
    return Vector2d<float>(static_cast<float>(state.x),static_cast<float>(state.y));
}

float MouseHandler::x() {
    return static_cast<float>(state.x);
}

float MouseHandler::y() {
    return static_cast<float>(state.y);
}

int MouseHandler::z() {
    return wheel();
}

} // namespace meh
