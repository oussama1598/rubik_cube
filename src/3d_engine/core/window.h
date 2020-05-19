#pragma once

#include <stdexcept>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
    int _width{1000};
    int _height{800};

    GLFWwindow *_window;

private:
    static void _handle_errors(int, const char *description);

public:
    explicit Window(const std::string &title);

    ~Window();

    inline GLFWwindow *get_window() { return _window; }
};
