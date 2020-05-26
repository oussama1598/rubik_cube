#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "face_data.h"

class Cubie_Data {
private:
    glm::vec3 _position{0.f};
    std::vector<Face_Data *> _faces;

public:
    static const std::vector<glm::vec3> faces_normals;
    static const std::vector<std::string> faces_colors;

public:
    explicit Cubie_Data(glm::vec3 position);

    inline glm::vec3 &get_position() { return _position; }

    inline std::vector<Face_Data *> &get_faces() { return _faces; }

    void rotate(const glm::vec3 &axis);

    std::string get_face(const std::string &direction);
};

