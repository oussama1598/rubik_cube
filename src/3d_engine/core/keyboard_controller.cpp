#include "keyboard_controller.h"

Keyboard_Controller::Keyboard_Controller(GLFWwindow *window) : _window(window) {}

void Keyboard_Controller::update() {
    _on_button_clicked();
}
