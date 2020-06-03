#pragma once

#include "custom_contour.h"
#include "viewer.h"
#include <opencv2/opencv.hpp>

class Rubik_Detector {

private:
    std::string _config_file{"config.json"};

    std::map<std::string, bool> _windows_states{
            {"output",   true},
            {"gray",     false},
            {"no_noise", false},
            {"canny",    false},
            {"dilated",  false}
    };

    std::string _calibrate_color{""};

    std::map<std::string, int> _blur_settings{
            {"kernel_x", 15},
            {"kernel_y", 15},
            {"sigma_x",  2},
            {"sigma_y",  2}
    };

    std::map<std::string, int> _canny_settings{
            {"threshold1", 10},
            {"threshold2", 16}
    };

    std::map<std::string, int> _dilated_settings{
            {"kernel_x",   3},
            {"kernel_y",   3},
            {"iterations", 4}};


    std::map<std::string, cv::Scalar> _color_mapping{
            {"White",  {255, 255, 255}},
            {"Orange", {0,   165, 255}},
            {"Green",  {0,   255, 0}},
            {"Blue",   {255, 0,   0}},
            {"Yellow", {0,   255, 255}},
            {"Red",    {0,   0,   255}},
            {"",       {0,   0,   0}}
    };

    std::map<std::string, std::pair<cv::Scalar, cv::Scalar>> _color_ranges{
            {
                    "White",  {
                                      {140, 190, 180},
                                      {255, 225, 240}
                              }
            },
            {
                    "Orange", {
                                      {200, 105, 0},
                                      {230, 155, 65}
                              }
            },
            {
                    "Green",  {
                                      {0,   120, 80},
                                      {5,   150, 140}
                              }
            },
            {
                    "Blue",   {
                                      {0,   150, 207},
                                      {5,   185, 255}
                              }
            },
            {
                    "Yellow", {
                                      {185, 180, 30},
                                      {250, 255, 100}
                              }
            },
            {
                    "Red",    {
                                      {255, 0,   0},
                                      {255, 0,   0}
                              }
            }
    };

    bool _save_settings{false};

    cv::Mat _image;
    cv::Mat _gray;
    cv::Mat _no_noise;
    cv::Mat _canny;
    cv::Mat _dilated;

    cv::Scalar _min{INFINITY, INFINITY, INFINITY};
    cv::Scalar _max{-INFINITY, -INFINITY, -INFINITY};

    int _mean_square_area{0};

    int _median_square_width{0};
    int _top{-1};

    int _bottom{-1};
    int _left{-1};
    int _right{-1};
    std::map<std::string, std::array<std::string, 9>> _data{
            {"U", {}},
    };

    Viewer viewer{&_windows_states, &_calibrate_color, &_blur_settings, &_canny_settings,
                  &_dilated_settings, &_color_ranges, &_save_settings};

private:
    void _dump_settings();

    std::vector<Custom_Contour>
    _remove_non_square(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour>
    _remove_greater_than_candidates(std::vector<Custom_Contour> &candidates,
                                    int area_cutoff);

    void _calculate_median_square_area(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour>
    _remove_less_than_candidates(std::vector<Custom_Contour> &candidates,
                                 int area_cutoff);

    std::pair<int, int>
    _get_contour_neighbors(std::vector<Custom_Contour> &candidates,
                           Custom_Contour &contour) const;

    void _get_cube_boundary(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour>
    _remove_squares_outside_cube(std::vector<Custom_Contour> &candidates) const;

    bool _sanity_check_results(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour>
    _sort_by_row_col(std::vector<Custom_Contour> candidates);

    void _analyze();

    void _draw_cube_face();

public:

    Rubik_Detector();

    std::string _get_color_name(cv::Scalar &color);
};
