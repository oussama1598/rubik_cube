#pragma once

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext/matrix_transform.hpp>

class Face_Data {
private:
    float _scale{.95f};
    glm::vec3 _normal;
    glm::vec3 _default_normal;
    char _color{};

public:
    Face_Data(glm::vec3 normal, char color);

    [[nodiscard]] inline float get_scale() const { return _scale; }

    inline glm::vec3 get_normal() {
        return _normal;
    }

    inline glm::vec3 &get_default_normal() { return _default_normal; }

    inline char get_color() const { return _color; }

    void rotate(float angle, const glm::vec3 &axis);
};

