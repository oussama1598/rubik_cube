#include "image.h"

Image::Image(cv::Mat &frame) {
    _width = frame.cols;
    _height = frame.rows;

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR,
                 GL_UNSIGNED_BYTE, (frame.data));
}

Image::~Image() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &_id);
}
