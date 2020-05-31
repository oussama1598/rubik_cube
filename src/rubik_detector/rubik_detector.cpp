#include "rubik_detector.h"

Rubik_Detector::Rubik_Detector() {
    _image = cv::imread(
            "/home/red-scule/Desktop/projects/cpp_projects/rubik_cube/assets/2.jpg", 1);

    int width{352};
    int height{240};

    auto cap = cv::VideoCapture(0);

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);

    cv::namedWindow("Fig", cv::WINDOW_NORMAL);
    cv::resizeWindow("Fig", width * 2, height * 2);

    // video saving
//    cv::VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 24,
//                          cv::Size(cap.get(cv::CAP_PROP_FRAME_WIDTH),
//                                   cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    while (cv::waitKey(1) != 113) {
        cap >> _image;

        _analyze();
        _draw_cube_face();

        cv::imshow("Fig", _image);

//        video.write(_image);

    }

    // Clean up window and erase it
    cap.release();
    cv::destroyAllWindows();
}

std::vector<Custom_Contour>
Rubik_Detector::_remove_non_square(std::vector<Custom_Contour> &candidates) {
    std::vector<Custom_Contour> results;

    for (auto &contour: candidates) {
        if (contour.is_square()) {
            results.push_back(contour);
        }
    }

    return results;
}

std::vector<Custom_Contour>
Rubik_Detector::_remove_greater_than_candidates(std::vector<Custom_Contour> &candidates,
                                                int area_cutoff) {
    std::vector<Custom_Contour> results;

    for (auto &contour: candidates) {
        if (contour.get_area() < area_cutoff) {
            results.push_back(contour);
        }
    }

    return results;
}

void Rubik_Detector::_calculate_median_square_area(std::vector<Custom_Contour> &candidates) {
    std::vector<int> square_areas;
    std::vector<int> square_widths;

    int total_square_area{0};

    for (auto &contour: candidates) {
        square_areas.push_back(contour.get_area());
        square_widths.push_back(contour.get_width());

        total_square_area += (int) contour.get_area();
    }

    if (!square_areas.empty()) {
        std::sort(square_areas.begin(), square_areas.end());
        std::sort(square_widths.begin(), square_widths.end());

        int num_of_squares = candidates.size();

        // Do not take the exact median, take the one 2/3 of the way through
        // the list. Sometimes you get clusters of smaller squares which can
        // throw us off if we take the exact median.
        int middle_square_index = (int) ((2 * num_of_squares) / 3);

        _mean_square_area = (int) (total_square_area / num_of_squares);
        _median_square_area = (int) square_areas[middle_square_index];
        _median_square_width = (int) square_widths[middle_square_index];
    }
}


std::vector<Custom_Contour>
Rubik_Detector::_remove_less_than_candidates(std::vector<Custom_Contour> &candidates,
                                             int area_cutoff) {
    std::vector<Custom_Contour> results;

    for (auto &contour: candidates) {
        if (contour.get_area() > area_cutoff) {
            results.push_back(contour);
        }
    }

    return results;
}

std::pair<int, int> Rubik_Detector::_get_contour_neighbors(std::vector<Custom_Contour> &candidates,
                                                           Custom_Contour &current_contour) const {
    const float WIGGLE_THRESHOLD = .5f;

    int width_wiggle = (int) ((float) _median_square_width * WIGGLE_THRESHOLD);
    int height_wiggle = (int) ((float) _median_square_width * WIGGLE_THRESHOLD);

    int row_neighbors{0};
    int col_neighbors{0};

    for (Custom_Contour &contour: candidates) {
        // do not check against the searched contour
        if (&contour == &current_contour) continue;

        int x_delta = std::abs(contour.get_cX() - current_contour.get_cX());
        int y_delta = std::abs(contour.get_cY() - current_contour.get_cY());

        if (x_delta <= width_wiggle) {
            col_neighbors += 1;
        }

        if (y_delta <= height_wiggle) {
            row_neighbors += 1;
        }
    }

    return {row_neighbors, col_neighbors};
}

void Rubik_Detector::_get_cube_boundary(std::vector<Custom_Contour> &candidates) {
    _top = _bottom = _left = _right = -1;

    for (auto &contour: candidates) {
        std::pair<int, int> neighbors = _get_contour_neighbors(candidates, contour);

        if (neighbors.first == 0 || neighbors.second == 0) continue;

        if (_top == -1 || contour.get_cY() < _top) _top = contour.get_cY();
        if (_bottom == -1 || contour.get_cY() > _bottom) _bottom = contour.get_cY();
        if (_left == -1 || contour.get_cX() < _left) _left = contour.get_cX();
        if (_right == -1 || contour.get_cY() > _right) _right = contour.get_cX();
    }
}

std::vector<Custom_Contour>
Rubik_Detector::_remove_squares_outside_cube(std::vector<Custom_Contour> &candidates) const {
    std::vector<Custom_Contour> results;

    int top = _top - (int) (_median_square_width / 2);
    int bottom = _bottom + (int) (_median_square_width / 2);
    int left = _left - (int) (_median_square_width / 2);
    int right = _right + (int) (_median_square_width / 2);

    for (auto &contour: candidates) {
        if (contour.get_cY() > top && contour.get_cY() < bottom && contour.get_cX() > left &&
            contour.get_cX() < right)
            results.push_back(contour);
    }

    return results;
}


bool Rubik_Detector::_sanity_check_results(std::vector<Custom_Contour> &candidates) {
    int num_of_squares = candidates.size();
    int needed_squares = 9;
    int requires_neighbors = 2;

    if (num_of_squares < needed_squares) {
        // Not enough squares

        return false;
    }

    for (auto &contour: candidates) {
        std::pair<int, int> neighbors = _get_contour_neighbors(candidates, contour);

        if (neighbors.second != requires_neighbors || neighbors.first != requires_neighbors) {
            std::cout << "Not enough cols/rows neighbors" << std::endl;

            return false;
        }
    }

    return true;
}

std::vector<Custom_Contour>
Rubik_Detector::_sort_by_row_col(std::vector<Custom_Contour> candidates) {
    std::vector<Custom_Contour> results;

    for (int i = 0; i < 3; ++i) {
        std::vector<Custom_Contour> tmp{candidates};

        std::sort(tmp.begin(), tmp.end(), [](const Custom_Contour &p1, const Custom_Contour &p2) {
            return p1.get_cY() < p2.get_cY();
        });

        std::vector<Custom_Contour> top_row;

        for (int j = 0; j < 3; ++j)
            top_row.push_back(tmp[j]);

        std::sort(top_row.begin(), top_row.end(),
                  [](const Custom_Contour &p1, const Custom_Contour &p2) {
                      return p1.get_cX() < p2.get_cX();
                  });

        for (int j = 0; j < 3; ++j) {
            results.push_back(top_row[j]);

            auto position = std::find_if(candidates.begin(), candidates.end(),
                                         [&](const Custom_Contour &c1) {
                                             return c1.get_index() == top_row[j].get_index();
                                         });

            if (position != candidates.end())
                candidates.erase(position);
        }
    }

    return results;
}

std::string Rubik_Detector::_get_color_name(cv::Scalar &color) {
    for (auto &c: _color_ranges) {
        cv::Scalar start = c.second.first;
        cv::Scalar end = c.second.second;

        if (Utils::in_range(color, start, end)) {
            return c.first;
        }
    }

    return std::string();
}


void Rubik_Detector::_analyze() {
    int img_width = _image.cols;
    int img_height = _image.rows;
    int img_area = img_width * img_height;

    cv::Mat gray;
    cv::cvtColor(_image, gray, cv::COLOR_BGR2GRAY);

    // look into changing this
    cv::Mat no_noise;
    cv::blur(gray, no_noise, cv::Size(10, 10));
//    cv::fastNlMeansDenoising(gray, no_noise, 10, 15, 7);

    cv::Mat canny;
    cv::Canny(no_noise, canny, 5, 10);

    cv::Mat kernel(3, 3, CV_8UC1, cv::Scalar(1));
    cv::Mat dilated;
    cv::dilate(canny, dilated, kernel, cv::Point(-1, -1), 4);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(dilated, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<Custom_Contour> candidates;

    for (size_t i = 0; i < contours.size(); ++i) {
        Custom_Contour contour = Custom_Contour(i, contours[i], hierarchy[i]);

        if (contour.get_area() > 30) {
            candidates.push_back(contour);
        }
    }

    candidates = _remove_non_square(candidates);

    // remove squares that take 1/4 of the image
    candidates = _remove_greater_than_candidates(candidates, img_area / 4);

    // get median
    _calculate_median_square_area(candidates);

    // remove squares that are less than half the mean square area
    candidates = _remove_less_than_candidates(candidates, _mean_square_area / 2);

    // recalculate the medians incase of changes
    _calculate_median_square_area(candidates);

    // remove squares that are greater than two times the mean square area
    candidates = _remove_greater_than_candidates(candidates, _mean_square_area * 2);

    // get cube boundaries
    _get_cube_boundary(candidates);

    // remove squares that are outside the boundaries
    candidates = _remove_squares_outside_cube(candidates);

    // recalculate the medians incase of changes
    _calculate_median_square_area(candidates);

    // show rectangles
    for (auto &cont: candidates) {
        cv::RotatedRect rect = cv::minAreaRect(cont.get_contour());

        cv::rectangle(_image, rect.boundingRect(), cv::Scalar(0, 255, 0), 2);
    }

    // check if we have all the needed squares
    if (_sanity_check_results(candidates)) {

        // sort the candidates from left to right and from top to bottom
        candidates = _sort_by_row_col(candidates);

        for (size_t i = 0; i < candidates.size(); ++i) {
            auto &cont = candidates[i];

            cv::Mat mask(img_height, img_width, CV_8UC1, cv::Scalar(0));

            std::vector<std::vector<cv::Point>> conts{cont.get_contour()};
            cv::drawContours(mask, conts, 0, 255, -1);

            cv::Scalar color = cv::mean(_image, mask);
            std::string color_name = _get_color_name(color);

            if (color_name.empty()) continue;

            _data.at("U").at(i) = color_name;

            cv::putText(_image, _get_color_name(color), cv::Point(cont.get_cX(), cont.get_cY()),
                        cv::FONT_HERSHEY_PLAIN, .5f, _color_mapping.at(color_name));
        }
    }
}

void Rubik_Detector::_draw_cube_face() {
    int size = 20;

    for (int x = 0; x < 3; ++x)
        for (int y = 0; y < 3; ++y) {
            std::string color = _data.at("U").at(x * 3 + y);

            std::cout << color << std::endl;

            cv::Rect rect{x * size, y * size, (x + 1) * size, (y + 1) * size};

            cv::rectangle(
                    _image,
                    rect,
                    _color_mapping.at(color),
                    -1
            );
        }

}
