#include "rubik.h"

Rubik::Rubik() {
    for (int x = -1; x <= 1; ++x)
        for (int y = -1; y <= 1; ++y)
            for (int z = -1; z <= 1; ++z) {
                _cubies.push_back(new Cubie_Data({x, y, z}));
            }
}

Rubik::~Rubik() {
    for (auto *cubie: _cubies) {
        delete cubie;
    }
}

void Rubik::_sort_faces(std::vector<std::pair<char, glm::vec3>> &faces_vector,
                        const std::array<char, 3> axis_order, const glm::vec3 &direction) {
    for (char axe: axis_order) {
        if (axe == 'x')
            std::sort(faces_vector.begin(), faces_vector.end(),
                      [direction](const std::pair<char, glm::vec3> &lhs,
                                  const std::pair<char, glm::vec3> &rhs) {
                          return direction.x * lhs.second.x < direction.x * rhs.second.x;
                      });

        if (axe == 'y')
            std::sort(faces_vector.begin(), faces_vector.end(),
                      [direction](const std::pair<char, glm::vec3> &lhs,
                                  const std::pair<char, glm::vec3> &rhs) {
                          return direction.y * lhs.second.y > direction.y * rhs.second.y;
                      });

        if (axe == 'z')
            std::sort(faces_vector.begin(), faces_vector.end(),
                      [direction](const std::pair<char, glm::vec3> &lhs,
                                  const std::pair<char, glm::vec3> &rhs) {
                          return direction.z * lhs.second.z < direction.z * rhs.second.z;
                      });
    }
}

void Rubik::rotate(const Move &move) {
    for (auto *cubie: _cubies) {
        if (move.axe == 'x' && (move.all_cubies || cubie->get_position().x == move.side)) {
            cubie->rotate({move.direction * 1.f, 0.f, 0.f});
        }

        if (move.axe == 'y' && (move.all_cubies || cubie->get_position().y == move.side)) {
            cubie->rotate({0.f, move.direction * 1.f, 0.f});
        }

        if (move.axe == 'z' && (move.all_cubies || cubie->get_position().z == move.side)) {
            cubie->rotate({0.f, 0.f, move.direction * 1.f});
        }
    }
}

void Rubik::apply_moves(const std::string &moves) {
    std::vector<std::string> moves_commands;

    boost::split(moves_commands, moves, boost::is_any_of(" "));

    for (std::string &move: moves_commands) {
        int repeats = 1;

        if (move.length() > 2) {
            repeats = std::stoi(std::string(1, move[1]));

            move.erase(move.begin() + 1, move.end() - 1);
        } else if (move.length() > 1 && move[1] != '\'') {
            repeats = std::stoi(std::string(1, move[1]));

            move.erase(move.begin() + 1, move.end());
        }

        for (int i = 0; i < repeats; ++i) {
            rotate(_moves.at(move));
        }
    }
}

std::string Rubik::to_string() {
    std::stringstream cube;

    std::map<char, std::vector<std::pair<char, glm::vec3 >>> faces{
            {'U', {}},
            {'D', {}},
            {'F', {}},
            {'B', {}},
            {'L', {}},
            {'R', {}}
    };

    for (Cubie_Data *cubie: _cubies) {
        if (cubie->get_position().y == 1) {
            faces.at('U').push_back({cubie->get_face('U'), cubie->get_position()});
        }

        if (cubie->get_position().y == -1) {
            faces.at('D').push_back({cubie->get_face('D'), cubie->get_position()});
        }

        if (cubie->get_position().z == 1) {
            faces.at('F').push_back({cubie->get_face('F'), cubie->get_position()});
        }

        if (cubie->get_position().z == -1) {
            faces.at('B').push_back({cubie->get_face('B'), cubie->get_position()});
        }

        if (cubie->get_position().x == -1) {
            faces.at('L').push_back({cubie->get_face('L'), cubie->get_position()});
        }

        if (cubie->get_position().x == 1) {
            faces.at('R').push_back({cubie->get_face('R'), cubie->get_position()});
        }
    }

    for (char side: {'U', 'L', 'F', 'R', 'B', 'D'}) {
        auto &side_faces = faces.at(side);

        glm::vec3 direction{1.f, 1.f, 1.f};
        std::array<char, 3> axis_order{'x', 'y', 'z'};

        switch (side) {
            case 'R':
                direction.z = -1.f;
                axis_order = {'z', 'x', 'y'};
                break;
            case 'D':
                direction.z = -1.f;
                axis_order = {'x', 'z', 'y'};
                break;
            case 'B':
                direction.x = -1.f;
                break;
            case 'L':
                axis_order = {'z', 'x', 'y'};
                break;
            default:
                break;
        }

        _sort_faces(side_faces, axis_order, direction);

        for (auto &face: side_faces) {
            cube << face.first;
        }
    }

    return cube.str();
}
