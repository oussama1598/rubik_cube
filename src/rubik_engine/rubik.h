#pragma once

#include <vector>
#include <string>

#include "cubie_data.h"

class Rubik {
private:
    std::vector<Cubie_Data *> _cubies;

public:
    Rubik();

    ~Rubik();

    inline std::vector<Cubie_Data *> &get_cubies() { return _cubies; }

    void rotate(char axe);
};
