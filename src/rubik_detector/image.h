#pragma once

#include <GL/glew.h>
#include <opencv4/opencv2/core/mat.hpp>

class Image {
private:
    int _width{0};
    int _height{0};

    GLuint _id{};

public:
    explicit Image(cv::Mat &frame);

    ~Image();

    [[nodiscard]] void* get_id() const { return (void*)(intptr_t)_id; }

    [[nodiscard]] std::pair<int, int> get_size() const { return {_width, _height}; }
};

