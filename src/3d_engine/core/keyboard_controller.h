#pragma once

#include <functional>

#include "GLFW/glfw3.h"

class Keyboard_Controller {
public:
    typedef std::function<void()> button_clicked_callback;

private:
    GLFWwindow *_window;

    button_clicked_callback _on_button_clicked;

public:
    explicit Keyboard_Controller(GLFWwindow *window);

    inline void
    set_on_button_clicked(button_clicked_callback callback) { _on_button_clicked = callback; }

    inline bool is_key_pressed(int key) { return glfwGetKey(_window, key) == GLFW_PRESS; }

    void update();
};

