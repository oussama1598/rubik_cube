#include "mouse_controller.h"

Mouse_Controller::Mouse_Controller(GLFWwindow *window) : _window(window) {}

void Mouse_Controller::update() {
    glfwGetCursorPos(_window, &_mouse_x, &_mouse_y);

    if (_first_move) {
        _last_mouse_x = _mouse_x;
        _last_mouse_y = _mouse_y;
        _first_move = false;
    }

    _mouse_offset_x = _mouse_x - _last_mouse_x;
    _mouse_offset_y = _mouse_y - _last_mouse_y;

    _last_mouse_x = _mouse_x;
    _last_mouse_y = _mouse_y;

    _mouse_handler();
}
