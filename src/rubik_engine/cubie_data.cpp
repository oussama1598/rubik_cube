#include "cubie_data.h"

const std::vector<glm::vec3> Cubie_Data::faces_normals{
        {1.f,  0.f,  0.f}, // RIGHT
        {-1.f, 0.f,  0.f}, // LEFT
        {0.f,  1.f,  0.f}, // TOP
        {0.f,  -1.f, 0.f}, // DOWN
        {0.f,  0.f,  1.f}, // FRONT
        {0.f,  0.f,  -1.f} // BACK
};

const std::vector<std::string> Cubie_Data::faces_colors{
        "red", // RIGHT
        "orange", // LEFT
        "white", // TOP
        "yellow", // DOWN
        "green", // FRONT
        "blue" // BACK
};

Cubie_Data::Cubie_Data(glm::vec3 position) : _position(position) {
    if (position.x == 1 && position.y == 1 && position.z == 1) {
        highlight = 1;
    }

    for (int i = 0; i < 6; ++i) {
        _faces.push_back(
                new Face_Data(faces_normals[i], faces_colors[i])
        );
    }
}

void Cubie_Data::rotate(const glm::vec3 &axis) {
    const float angle{90.f};

    _position = glm::round(glm::rotate(_position, glm::radians(angle), axis));

    for (auto *face: _faces) {
        face->rotate(angle, axis);
    }
}
