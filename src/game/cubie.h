#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "3d_engine/renderer/object.h"

class Cubie {
private:
    float _scale{.98f};

    glm::vec3 _position;

    std::vector<Object *> _faces;

public:
    explicit Cubie(const glm::vec3 &position);

    inline std::vector<Object *> &get_faces() { return _faces; }

    inline void add_face(Object *face) { _faces.push_back(face); }
};

