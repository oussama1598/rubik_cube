#include "rubik_cube.h"
#include "rubik_engine/rubik.h"
#include "rubik_detector/rubik_detector.h"

int main() {
    Rubik rubik_engine;

    rubik_engine.apply_moves("L2 R' U2 D2 B L B2 F R D R' L' D2 B' F2 R2 F U L' R2");

    rubik_engine.apply_moves("z' U B2 R' D' B' F D' L D");

    Rubik_Cube rubik_cube{&rubik_engine};
    rubik_cube.start();

//    Rubik_Detector rubik_detector;
}
