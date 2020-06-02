#include <filesystem>
#include "utils.h"


bool Utils::file_exists(const std::string &file_path) {
    return std::filesystem::exists(file_path);
}

void Utils::save_file(const std::string &file_path, nlohmann::json &json) {
    std::ofstream file(file_path);

    if (file.is_open()) {
        file << json.dump(3);

        file.close();
    }
}

nlohmann::json Utils::load_json(const std::string &file_path) {
    std::ifstream file(file_path);
    nlohmann::json json_content;

    if (!file.is_open()) {
        return {};
    }

    file >> json_content;

    file.close();

    return json_content;
}

double Utils::get_angle(const cv::Point &A, const cv::Point &B, const cv::Point &C) {
    // returns the angle ACB

    /*  C
       / \
    b /   \ a
     /     \
    A-------B
        c
     */

    double a = pixel_distance(C, B);
    double b = pixel_distance(A, C);
    double c = pixel_distance(A, B);

    // Cosine Rule
    // https://www.mathsisfun.com/algebra/trig-cosine-law.html
    double cos_angle = (pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b);

    cos_angle = std::clamp<double>(cos_angle, -1, 1);

    return std::acos(cos_angle);
}

double Utils::pixel_distance(const cv::Point &A, const cv::Point &B) {
    return sqrt(
            pow(B.x - A.x, 2) + pow(B.y - A.y, 2)
    );
}

std::array<cv::Point, 4>
Utils::sort_corners(cv::Point &corner1, cv::Point &corner2, cv::Point &corner3,
                    cv::Point &corner4) {
    std::array<cv::Point, 4> corners
            {
                    corner1, corner2, corner3, corner4
            };

    std::array<cv::Point, 4> results;

    int min_x = INT_MAX;
    int min_y = INT_MAX;
    int max_x = INT_MIN;
    int max_y = INT_MIN;

    for (auto &corner: corners) {
        if (corner.x < min_x) min_x = corner.x;
        if (corner.y < min_y) min_y = corner.y;
        if (corner.x > max_x) max_x = corner.x;
        if (corner.y > max_y) max_y = corner.y;
    }

    double top_left_distance = INFINITY;
    double top_right_distance = INFINITY;
    double bottom_left_distance = INFINITY;
    double bottom_right_distance = INFINITY;

    for (auto &corner: corners) {
        double current_top_left_distance = pixel_distance(cv::Point(min_x, min_y), corner);

        if (current_top_left_distance < top_left_distance) {
            results[0] = corner;
            top_left_distance = current_top_left_distance;
        }

        double current_top_right_distance = pixel_distance(cv::Point(max_x, min_y), corner);

        if (current_top_right_distance < top_right_distance) {
            results[1] = corner;
            top_right_distance = current_top_right_distance;
        }

        double current_bottom_left_distance = pixel_distance(cv::Point(min_x, max_y), corner);

        if (current_bottom_left_distance < bottom_left_distance) {
            results[2] = corner;
            bottom_left_distance = current_bottom_left_distance;
        }

        double current_bottom_right_distance = pixel_distance(cv::Point(max_x, max_y), corner);

        if (current_bottom_right_distance < bottom_right_distance) {
            results[3] = corner;
            bottom_right_distance = current_bottom_right_distance;
        }
    }

    return results;
}


std::pair<int, int> Utils::square_width_height(std::vector<cv::Point> &approx) {
    std::array<cv::Point, 4> corners = sort_corners(
            approx[0],
            approx[1],
            approx[2],
            approx[3]
    );

    double AB = pixel_distance(corners[0], corners[1]);
    double AC = pixel_distance(corners[0], corners[2]);
    double DB = pixel_distance(corners[3], corners[1]);
    double DC = pixel_distance(corners[3], corners[2]);

    return {
            std::max(AB, DC),
            std::max(AC, DB)
    };
}

bool Utils::approx_is_square(std::vector<cv::Point> &approx) {
    const float SIDE_VS_SIDE_THRESHOLD = .6f;
    const int ANGLE_THRESHOLD = 20;
    const int ROTATE_THRESHOLD = 30;

    // if the corners are more than for points this is diffidently not a square
    if (approx.size() != 4)
        return false;

    std::array<cv::Point, 4> corners = sort_corners(
            approx[0],
            approx[1],
            approx[2],
            approx[3]
    );

    cv::Point &A = corners[0];
    cv::Point &B = corners[1];
    cv::Point &C = corners[2];
    cv::Point &D = corners[3];

    // A---B
    // |   |
    // D---D


    // this is to tolerate some differences in each side of the square
    // it doesnt have to be a perfect square

    double AB = pixel_distance(A, B);
    double AC = pixel_distance(A, C);
    double DB = pixel_distance(D, B);
    double DC = pixel_distance(D, C);

    double max_distance = std::max({AB, AC, DB, DC});

    int cut_off = (int) (max_distance * SIDE_VS_SIDE_THRESHOLD);

    for (double distance: {AB, AC, DB, DC}) {
        if (distance < cut_off)
            return false;
    }

    int min_angle = 90 - ANGLE_THRESHOLD;
    int max_angle = 90 + ANGLE_THRESHOLD;

    int angle_A = (int) (get_angle(C, B, A) * (180 / M_PI));
    if (angle_A < min_angle || angle_A > max_angle)
        return false;

    int angle_B = (int) (get_angle(A, D, B) * (180 / M_PI));
    if (angle_B < min_angle || angle_B > max_angle)
        return false;

    int angle_C = (int) (get_angle(A, D, C) * (180 / M_PI));
    if (angle_C < min_angle || angle_C > max_angle)
        return false;

    int angle_D = (int) (get_angle(C, B, D) * (180 / M_PI));
    if (angle_D < min_angle || angle_D > max_angle)
        return false;

    int far_left = std::min({A.x, B.x, C.x, D.x});
    int far_right = std::max({A.x, B.x, C.x, D.x});
    int far_up = std::min({A.y, B.y, C.y, D.y});

    cv::Point top_left{far_left, far_up};
    cv::Point top_right{far_right, far_up};

    // is AB horizontal
    if (B.y < A.y) {
        angle_B = (int) (get_angle(A, top_left, B) * (180 / M_PI));

        if (angle_B > ROTATE_THRESHOLD)
            return false;
    } else {
        angle_A = (int) (get_angle(B, top_right, A) * (180 / M_PI));

        if (angle_A > ROTATE_THRESHOLD)
            return false;
    }

    return true;
}

bool Utils::in_range(const cv::Scalar &p, const cv::Scalar &start, const cv::Scalar &end) {
    return (start[0] <= p[2] && p[2] <= end[0]) &&
           (start[1] <= p[1] && p[1] <= end[1]) &&
           (start[2] <= p[0] && p[0] <= end[2]);
}
