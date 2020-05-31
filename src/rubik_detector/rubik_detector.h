#pragma once

#include <opencv2/opencv.hpp>
#include "custom_contour.h"

class Rubik_Detector {

private:
    cv::Mat _image;

    int _mean_square_area{0};
    int _median_square_area{0};
    int _median_square_width{0};

    int _top{-1};
    int _bottom{-1};
    int _left{-1};
    int _right{-1};

    std::map<std::string, std::array<std::string, 9>> _data{
            {"U", {}},
    };

    std::map<std::string, std::pair<cv::Scalar, cv::Scalar>> _color_ranges{
            {
                    "white",  {
                                      {0,   0,   120},
                                      {255, 50,  255}
                              }
            },
            {
                    "orange", {
                                      {175, 180, 155},
                                      {10,  255, 255}
                              }
            }
    };

    std::map<std::string, cv::Scalar> _color_mapping{
            {"white",  {255, 255, 255}},
            {"orange", {255, 165, 0}},
            {"",       {0,   0,   0}}
    };

private:
    std::vector<Custom_Contour> _remove_non_square(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour>
    _remove_greater_than_candidates(std::vector<Custom_Contour> &candidates, int area_cutoff);

    void _calculate_median_square_area(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour>
    _remove_less_than_candidates(std::vector<Custom_Contour> &candidates, int area_cutoff);

    std::pair<int, int>
    _get_contour_neighbors(std::vector<Custom_Contour> &candidates, Custom_Contour &contour) const;

    void _get_cube_boundary(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour>
    _remove_squares_outside_cube(std::vector<Custom_Contour> &candidates) const;

    bool _sanity_check_results(std::vector<Custom_Contour> &candidates);

    std::vector<Custom_Contour> _sort_by_row_col(std::vector<Custom_Contour> candidates);

    void _analyze();

    void _draw_cube_face();

public:

    Rubik_Detector();

    std::string _get_color_name(cv::Scalar &color);
};

