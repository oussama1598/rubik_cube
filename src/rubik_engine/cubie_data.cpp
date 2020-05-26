#include "cubie_data.h"

const std::vector<glm::vec3> Cubie_Data::faces_normals{
        {1.f,  0.f,  0.f}, // RIGHT
        {-1.f, 0.f,  0.f}, // LEFT
        {0.f,  1.f,  0.f}, // UP
        {0.f,  -1.f, 0.f}, // DOWN
        {0.f,  0.f,  1.f}, // FRONT
        {0.f,  0.f,  -1.f} // BACK
};

const std::vector<std::string> Cubie_Data::faces_colors{
        "R", // RIGHT
        "L", // LEFT
        "U", // UP
        "D", // DOWN
        "F", // FRONT
        "B" // BACK
//        "red", // RIGHT
//        "orange", // LEFT
//        "white", // UP
//        "yellow", // DOWN
//        "green", // FRONT
//        "blue" // BACK
};

Cubie_Data::Cubie_Data(glm::vec3 position) : _position(position) {
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

std::string Cubie_Data::get_face(const std::string &direction) {
    std::map<std::string, int> index_to_normals{
            {"R", 0},
            {"L", 1},
            {"U", 2},
            {"D", 3},
            {"F", 4},
            {"B", 5}
    };

    glm::vec3 normal = faces_normals[index_to_normals.at(direction)] * .5f;

    for (Face_Data *face: _faces) {
        glm::vec3 scaled_normal = normal * face->get_scale();

        if (glm::all(glm::lessThan(glm::abs(face->get_normal() - scaled_normal),
                                   glm::vec3(0.00001)))) {
            return face->get_color();
        }
    }

    return "";
}
