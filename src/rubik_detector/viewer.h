#pragma once

#include <stdexcept>
#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "vendor/imgui_impl_glfw.h"
#include "vendor/imgui_impl_opengl3.h"

#include "image.h"

class Viewer {
private:
    int _width{1100};
    int _height{800};

    std::string _title{"Rubik Detector"};

    GLFWwindow *_window;

    std::map<std::string, Image *> _images;

    std::map<std::string, bool> *_windows_states;

private:
    static void _handle_errors(int, const char *description);

    void _build_gui();

    void _clear_gui();

public:
    Viewer(std::map<std::string, bool> *window_states);

    [[nodiscard]] bool is_running() const { return !glfwWindowShouldClose(_window); }

    void add_frame(const std::string &title, cv::Mat &frame);

    void render();
};

