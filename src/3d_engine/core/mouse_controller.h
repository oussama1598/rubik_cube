#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Mouse_Controller {
private:

    GLFWwindow *_window;

    bool _first_move{false};
    double _mouse_x;
    double _mouse_y;
    double _last_mouse_x;
    double _last_mouse_y;
    double _mouse_offset_x;
    double _mouse_offset_y;

public:
    typedef std::function<void()> mouse_handler;

private:
    mouse_handler _mouse_handler;

public:
    Mouse_Controller(GLFWwindow *window);

    inline void
    set_mouse_handler(mouse_handler callback) { _mouse_handler = callback; }

    inline bool is_right_button_clicked() {
        return glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    }

    inline glm::vec2 get_mouse_offset() {
        return {_mouse_offset_x, _mouse_offset_y};
    }

    void update();
};

