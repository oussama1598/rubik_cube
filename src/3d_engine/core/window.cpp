#include "window.h"

Window::Window(const std::string &title) {
    glfwSetErrorCallback(_handle_errors);

    if (!glfwInit())
        std::runtime_error("Could not load glfw.");

    // window options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = glfwCreateWindow(_width, _height, title.c_str(), nullptr, nullptr);

    if (!_window)
        throw std::runtime_error("Could not create the glfw window.");

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Could not initialize glew.");

    std::cout << "OpenGL version supported by this platform: " << glGetString(GL_VERSION) << " "
              << glGetString(GL_VENDOR)
              << std::endl;
}

Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Window::_handle_errors(int, const char *description) {
    throw std::runtime_error("Error: " + std::string(description));
}
