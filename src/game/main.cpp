#include <iostream>

#include "rubik_cube.h"
#include "rubik_engine/rubik.h"

int main() {
    Rubik rubik_engine;

    rubik_engine.rotate('x');
    rubik_engine.rotate('x');
    rubik_engine.rotate('y');
    rubik_engine.rotate('y');
    rubik_engine.rotate('z');

    Rubik_Cube rubik_cube{&rubik_engine};
    rubik_cube.start();
}
