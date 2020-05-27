#include "rubik_detector.h"

Rubik_Detector::Rubik_Detector() {
    cv::Mat src = cv::imread(
            "/home/red-scule/Desktop/projects/cpp_projects/rubik_cube/assets/2.jpg", 1);

    auto cap = cv::VideoCapture(0);

    while (cv::waitKey(1) != 113) {
        cap.read(src);


        cv::Mat gray_image;
        cv::cvtColor(src, gray_image, cv::COLOR_BGR2GRAY);

        cv::Mat kernel{5, 5};
        cv::GaussianBlur(gray_image, gray_image, cv::Size(5, 5), 0, 0);

        cv::Mat edges_image;
        cv::Canny(gray_image, edges_image, 50, 100);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::findContours(edges_image, contours, hierarchy, cv::RETR_EXTERNAL,
                         cv::CHAIN_APPROX_SIMPLE);

        std::vector<std::vector<cv::Point>> new_contours;

        for (auto &cont: contours) {
            cv::RotatedRect bound_rect = cv::minAreaRect(cont);

            double length = bound_rect.size.width;
            double breadth = bound_rect.size.height;

            if (std::max(length / breadth, breadth / length) > 1.5)
                continue;

//        if ((cv::contourArea(cont) / (length * breadth)) < 0.7)
//            continue;

            if (cv::contourArea(cont) < 5)
                continue;

            new_contours.push_back(cont);
        }

        for (auto &cont: new_contours) {
            cv::RotatedRect rect = cv::minAreaRect(cont);

            cv::rectangle(src, rect.boundingRect(), cv::Scalar(0, 255, 0), 2);
        }

        cv::Mat output(src.rows * 2, src.cols * 2, src.type());
        cv::Rect position(0, 0, src.cols, src.rows);

        cv::Mat gray_image_3_channels;
        cv::cvtColor(gray_image, gray_image_3_channels, cv::COLOR_GRAY2RGB);

        gray_image_3_channels.copyTo(output(position));

        cv::Mat edges_image_3_channels;
        cv::cvtColor(edges_image, edges_image_3_channels, cv::COLOR_GRAY2RGB);

        position.x = src.cols;
        edges_image_3_channels.copyTo(output(position));

        position.x = 0;
        position.y = src.rows;
        src.copyTo(output(position));

        cv::imshow("output", output);

    }

    // Clean up window and erase it
    cv::destroyAllWindows();
}
