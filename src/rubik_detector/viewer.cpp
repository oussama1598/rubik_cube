#include "viewer.h"

Viewer::Viewer() {
    if (!glfwInit())
        std::runtime_error("Could not load glfw.");

    // window options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);

    if (!_window)
        throw std::runtime_error("Could not create the glfw window.");

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
}
