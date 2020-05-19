#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "3d_engine/renderer/object.h"

class Cubie {
private:
    float _scale{.98f};

    std::vector<glm::vec3> _positions{
            {_scale * .5f,  0.f,   0.f}, // LEFT
            {-_scale * .5f, 0.f,   0.f}, // RIGHT
            {0.f,   _scale * .5f,  0.f}, // TOP
            {0.f,   -_scale * .5f, 0.f}, // DOWN
            {0.f,   0.f,   _scale * .5f}, // FRONT
            {0.f,   0.f,   -_scale * .5f} // BACK
    };

    std::vector<glm::vec3> _rotations{
            {0.f,  90.f, 0.f},
            {0.f,  90.f, 0.f},
            {90.f, 0.f,  0.f},
            {90.f, 0.f,  0.f},
            {0.f,  0.f,  0.f},
            {0.f,  0.f,  0.f}
    };

    std::vector<std::string> _colors{
            "orange", // LEFT
            "red", // RIGHT
            "white", // TOP
            "yellow", // DOWN
            "green", // FRONT
            "blue" // BACK
    };

    glm::vec3 _position;

    std::vector<Object *> _faces;

public:
    explicit Cubie(const glm::vec3 &position, std::map<std::string, Material *> materials);

    inline std::vector<Object *> &get_faces() { return _faces; }
};

