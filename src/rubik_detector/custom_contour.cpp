#include "custom_contour.h"

Custom_Contour::Custom_Contour(int index, std::vector<cv::Point> &contour, cv::Vec4i &heirarchy)
        : _index(index), _contour(contour), _heirarchy(heirarchy) {
    double peri = cv::arcLength(contour, true);

    cv::approxPolyDP(contour, _approx, 0.1 * peri, true);

    _area = cv::contourArea(contour);
    _corners = _approx.size();

    std::pair<int, int> size = Utils::square_width_height(_approx);

    _width = size.first;
    _height = size.second;

    cv::Moments M = cv::moments(contour);

    if (M.m00 != 0) {
        _cX = (int) (M.m10 / M.m00);
        _cY = (int) (M.m01 / M.m00);
    }
}

bool Custom_Contour::is_square() {
    return Utils::approx_is_square(_approx);
}
