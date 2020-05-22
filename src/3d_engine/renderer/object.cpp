#include "object.h"

Object::Object() {
    _calculate_model_matrix();
}

void Object::_calculate_model_matrix() {
    _model_matrix = glm::mat4{1.f};

    _model_matrix = glm::translate(_model_matrix, _position);
    // rotate_with_mouse along x
    _model_matrix = glm::rotate(_model_matrix, glm::radians(_rotation.x), glm::vec3(1.f, 0.f, 0.f));
    // rotate_with_mouse along y
    _model_matrix = glm::rotate(_model_matrix, glm::radians(_rotation.y), glm::vec3(0.f, 1.f, 0.f));
    // rotate_with_mouse along z
    _model_matrix = glm::rotate(_model_matrix, glm::radians(_rotation.z), glm::vec3(0.f, 0.f, 1.f));
    _model_matrix = glm::scale(_model_matrix, _scale);
}

void Object::move_to(const glm::vec3 &position) {
    _position = position;

    _calculate_model_matrix();
}

void Object::translate(const glm::vec3 &direction) {
    _model_matrix = glm::translate(_model_matrix, direction);
}

void Object::rotate(float angle, const glm::vec3 &axis) {
    _model_matrix = glm::rotate(_model_matrix, glm::radians(angle), axis);
}

void Object::scale(const glm::vec3 &scale) {
    _model_matrix = glm::scale(_model_matrix, scale);
}


void Object::render() {
    _shader->set_uniform_matrix_4_fv("model_matrix", _model_matrix);

    _shader->bind();
    _mesh->render();
    _shader->unbind();
}
