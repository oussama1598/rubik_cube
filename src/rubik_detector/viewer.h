#pragma once

#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Viewer {
private:
    int _width{400};
    int _height{400};

    std::string _title{"Rubik Detector"};

    GLFWwindow *_window;

public:
    Viewer();
};

