#include "face_data.h"

Face_Data::Face_Data(glm::vec3 normal, std::string color) : _normal(normal * .5f * _scale),
                                                            _default_normal({0.f, 0.f, 1.f}),
                                                            _color(color) {}

void Face_Data::rotate(float angle, const glm::vec3 &axis) {
    _normal = glm::rotate(_normal, glm::radians(angle), axis);
}
