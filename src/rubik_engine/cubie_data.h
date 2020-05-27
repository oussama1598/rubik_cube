#pragma once

#include <iostream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "face_data.h"

class Cubie_Data {
private:
    glm::vec3 _position{0.f};
    std::vector<Face_Data *> _faces{};

public:
    static const std::array<glm::vec3, 6> faces_normals;
    static const std::array<char, 6> faces_colors;
    static const std::map<char, int> index_to_normals;

public:
    explicit Cubie_Data(glm::vec3 position);

    inline glm::vec3 &get_position() { return _position; }

    inline std::vector<Face_Data *> &get_faces() { return _faces; }

    void rotate(const glm::vec3 &axis);

    char get_face(char direction);
};

