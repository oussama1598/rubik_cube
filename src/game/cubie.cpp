#include "cubie.h"

Cubie::Cubie(const glm::vec3 &position, std::map<std::string, Material *> materials) : _position(
        position) {
    for (int i = 0; i < 6; ++i) {
        Object *face = new Object();

        face->move_to(position + _positions[i]);
        face->rotate(_rotations[i]);
        face->scale(glm::vec3{_scale});

        face->set_material(materials.at(_colors.at(i)));

        _faces.push_back(face);
    }
}
