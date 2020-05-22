#include "rubik.h"

Rubik::Rubik() {
    for (int x = -1; x <= 1; ++x)
        for (int y = -1; y <= 1; ++y)
            for (int z = -1; z <= 1; ++z) {
                _cubies.push_back(new Cubie_Data({x, y, z}));
            }
}

Rubik::~Rubik() {

}

void Rubik::rotate(char axe) {
    for (auto *cubie: _cubies) {
        switch (axe) {
            case 'x':
                if (cubie->get_position().x == 1) {
                    cubie->rotate({1.f, 0.f, 0.f});
                }
                break;
            case 'y':
                if (cubie->get_position().y == 1) {
                    cubie->rotate({0.f, 1.f, 0.f});
                }
                break;
            case 'z':
                if (cubie->get_position().z == 1) {
                    cubie->rotate({0.f, 0.f, 1.f});
                }
                break;
        }
    }
}
