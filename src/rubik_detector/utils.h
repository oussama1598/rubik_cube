#pragma once

#include <utility>
#include <vector>
#include <fstream>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>

class Utils {
public:
    static bool file_exists(const std::string &file_path);

    static void save_file(const std::string &file_path, nlohmann::json &json);

    static nlohmann::json load_json(const std::string &file_path);

    static double get_angle(const cv::Point &A, const cv::Point &B, const cv::Point &C);

    static double pixel_distance(const cv::Point &A, const cv::Point &B);

    static std::array<cv::Point, 4>
    sort_corners(cv::Point &corner1, cv::Point &corner2, cv::Point &corner3, cv::Point &corner4);

    static std::pair<int, int> square_width_height(std::vector<cv::Point> &approx);

    static bool approx_is_square(std::vector<cv::Point> &approx);

    static bool in_range(const cv::Scalar &p, const cv::Scalar &start, const cv::Scalar &end);
};

