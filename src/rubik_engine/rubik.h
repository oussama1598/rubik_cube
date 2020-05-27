#pragma once

#include <vector>
#include <string>
#include <map>
#include <array>

#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

#include "cubie_data.h"

class Rubik {
private:
    struct Move {
        float direction;
        float side;
        char axe;
    };

    std::vector<Cubie_Data *> _cubies;

    std::map<std::string, Move> _moves{
            {"U",  {-1.f, 1.f,  'y'}},
            {"D",  {1.f,  -1.f, 'y'}},
            {"L",  {1.f,  -1.f, 'x'}},
            {"R",  {-1.f, 1.f,  'x'}},
            {"F",  {-1.f, 1.f,  'z'}},
            {"B",  {1.f,  -1.f, 'z'}},

            {"U'", {1.f,  1.f,  'y'}},
            {"D'", {-1.f, -1.f, 'y'}},
            {"L'", {-1.f, -1.f, 'x'}},
            {"R'", {1.f,  1.f,  'x'}},
            {"F'", {1.f,  1.f,  'z'}},
            {"B'", {-1.f, -1.f, 'z'}},
    };

private:
    void _sort_faces(std::vector<std::pair<char, glm::vec3>> &faces_vector,
                     std::array<char, 3> axis_order = {'x', 'y', 'z'},
                     const glm::vec3 &direction = {1.f, 1.f, 1.f});

public:

    Rubik();

    ~Rubik();

    inline std::vector<Cubie_Data *> &get_cubies() { return _cubies; }

    void rotate(float direction, float side, char axe);

    void apply_moves(const std::string &moves);

    std::string to_string();
};
