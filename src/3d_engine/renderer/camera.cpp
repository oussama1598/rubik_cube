#include "camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec2 &size, float field_of_view,
               float near_plane,
               float far_plane) : _position(position) {

    _projection_matrix = glm::perspective(
            glm::radians(field_of_view),
            (float) (size.x / size.y),
            near_plane,
            far_plane
    );

    _recalculate_view_matrix();
}

void Camera::_recalculate_view_matrix() {
    _front.x = cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
    _front.y = sin(glm::radians(_rotation.x));
    _front.z = sin(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));

    _front = glm::normalize(_front);
    _right = glm::normalize(glm::cross(_front, _world_up));

    _view_matrix = glm::lookAt(_position, _position + _front, _world_up);
}

void Camera::translate(glm::vec3 &position) {
    _position += position;

    _recalculate_view_matrix();
}

void Camera::rotate(glm::vec3 &rotation) {
    _rotation += rotation;

    _recalculate_view_matrix();
}
