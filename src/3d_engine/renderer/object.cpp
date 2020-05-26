#include "object.h"

void Object::reset_transform() {
    _model_matrix = glm::mat4{1.f};
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
