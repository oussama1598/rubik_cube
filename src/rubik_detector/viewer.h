#pragma once

#include <stdexcept>
#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>

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

    // settings
    std::map<std::string, bool> *_windows_states;
    std::string *_calibrate_color;
    std::map<std::string, int> *_blur_settings;
    std::map<std::string, int> *_canny_settings;
    std::map<std::string, int> *_dilated_settings;
    std::map<std::string, std::pair<cv::Scalar, cv::Scalar>> *_color_ranges;
    bool *_save_settings;

    std::string _c_color{"White"};

private:
    static void _handle_errors(int, const char *description);

    void _build_gui();

    void _clear_gui();

public:
    Viewer(std::map<std::string, bool> *windows_states,
           std::string *calibrate_color,
           std::map<std::string, int> *blur_settings,
           std::map<std::string, int> *canny_settings,
           std::map<std::string, int> *dilated_settings,
           std::map<std::string, std::pair<cv::Scalar, cv::Scalar>> *color_ranges,
           bool *save_settings);

    [[nodiscard]] bool is_running() const { return !glfwWindowShouldClose(_window); }

    void add_frame(const std::string &title, cv::Mat &frame);

    void render();
};

