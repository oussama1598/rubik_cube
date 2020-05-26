#include "rubik_cube.h"
#include "rubik_engine/rubik.h"
//#include "opencv2/opencv.hpp"

int main() {
    Rubik rubik_engine;

    rubik_engine.apply_moves("F");

    std::cout << rubik_engine.to_string() << std::endl;

    Rubik_Cube rubik_cube{&rubik_engine};
    rubik_cube.start();

//    std::vector<glm::vec3> a{
//            {1,  -1, 0},
//            {1, 1,  0}
//    };
//    std::sort(a.begin(), a.end(),
//              [](const glm::vec3 &lhs, const glm::vec3 &rhs) {
//                  // Sort in ascending order by key x, y priority
//                  return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
//              });
//
//    for (auto &vec: a) {
//        std::cout << glm::to_string(vec) << std::endl;
//    }

//    cv::Mat src = cv::imread(
//            "/home/red-scule/Desktop/projects/cpp_projects/rubik_cube/assets/2.jpg", 1);
//
//    auto cap = cv::VideoCapture(0);
//
//    while (cv::waitKey(1) != 113) {
//        cap.read(src);
//
//        cv::Mat hsv_image;
//        cv::cvtColor(src, hsv_image, cv::COLOR_BGR2HSV);
//
//        cv::Mat dst = src.clone();
//
//        cv::Mat open_kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Point(7, 7));
//        cv::Mat close_kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Point(5, 5));
//
//        std::vector<std::pair<cv::Scalar, cv::Scalar>> colors
//                {
//                        {cv::Scalar(0, 0, 120), cv::Scalar(255, 50, 255)},
//                        {cv::Scalar(95, 60, 70),   cv::Scalar(120, 255, 220)},
//                        {cv::Scalar(50, 100, 100), cv::Scalar(90, 255, 240)}
//                };

//        for (auto &color: colors) {
//            cv::Mat color_mask;
//
//            cv::inRange(image, color.first, color.second, color_mask);
//            cv::morphologyEx(color_mask, color_mask, cv::MORPH_RECT, open_kernel, cv::Point(-1, -1),
//                             1);
//            cv::morphologyEx(color_mask, color_mask, cv::MORPH_RECT, close_kernel,
//                             cv::Point(-1, -1), 5);
//
//            std::vector<std::vector<cv::Point>> contours;
//            std::vector<cv::Vec4i> hierarchy;
//
//            cv::findContours(color_mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//
//            std::vector<std::vector<cv::Point>> new_contours;
//
//            for (auto &cont: contours) {
//                cv::RotatedRect bound_rect = cv::minAreaRect(cont);
//
//                double length = bound_rect.size.width;
//                double breadth = bound_rect.size.height;
//
//                if (std::max(length / breadth, breadth / length) > 1.5)
//                    continue;
//
//                if ((cv::contourArea(cont) / (length * breadth)) < 0.7)
//                    continue;
//
//                if (cv::contourArea(cont) < 1000)
//                    continue;
//
//                new_contours.push_back(cont);
//            }
//
//            for (auto &cont: new_contours) {
//                cv::RotatedRect rect = cv::minAreaRect(cont);
//
//                cv::rectangle(dst, rect.boundingRect(), cv::Scalar(0, 255, 0), 2);
//            }
//        }
//
//        cv::imshow("dst", dst);
//
//        for (auto &color: colors) {
//            cv::Mat mask;
//            cv::inRange(hsv_image, color.first, color.second, mask);
//
//            std::vector<std::vector<cv::Point>> contours;
//            std::vector<cv::Vec4i> hierarchy;
//
//            cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//
//            std::vector<std::vector<cv::Point>> new_contours;
//
//            for (auto &cont: contours) {
//                cv::RotatedRect bound_rect = cv::minAreaRect(cont);
//
//                double length = bound_rect.size.width;
//                double breadth = bound_rect.size.height;
//
//                if (std::max(length / breadth, breadth / length) > 1.5)
//                    continue;
//
//                if ((cv::contourArea(cont) / (length * breadth)) < 0.7)
//                    continue;
//
//                if (cv::contourArea(cont) < 1000)
//                    continue;
//
//                new_contours.push_back(cont);
//            }
//
//            for (auto &cont: new_contours) {
//                cv::RotatedRect rect = cv::minAreaRect(cont);
//
//                cv::rectangle(dst, rect.boundingRect(), cv::Scalar(0, 255, 0), 2);
//            }
//        }
//        cv::imshow("dst", dst);
//    }
//
//    //Clean up window and erase it
//    cv::destroyAllWindows();
}
