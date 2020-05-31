#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

#include "utils.h"

class Custom_Contour {
private:
    int _index;
    int _width{-1};
    int _height{-1};
    double _area;
    int _corners;

    int _cX;
    int _cY;

    std::vector<cv::Point> _contour;
    cv::Vec4i _heirarchy;
    std::vector<cv::Point> _approx;

public:
    Custom_Contour(int index, std::vector<cv::Point> &contour, cv::Vec4i &heirarchy);

    [[nodiscard]] inline int get_index() const { return _index; }

    [[nodiscard]] inline std::vector<cv::Point> get_contour() const { return _contour; }

    [[nodiscard]] inline double get_area() const { return _area; }

    [[nodiscard]] inline int get_width() const { return _width; }

    [[nodiscard]] inline int get_cX() const { return _cX; }

    [[nodiscard]] inline int get_cY() const { return _cY; }

    bool is_square();
};

