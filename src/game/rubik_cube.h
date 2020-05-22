#pragma once

#include "3d_engine/core/engine.h"
#include "3d_engine/primitives/plane.h"

#include "rubik_engine/rubik.h"

#include "cubie.h"

class Rubik_Cube {

private:
    Engine *_game_engine{nullptr};
    Scene *_game_scene{nullptr};
    Rubik *_rubik;

private:
    void _init_game_engine();

    void _init_game_scene();

    void _init_cube();

    void _handle_keyboard_input();

    void _handler_mouse_input();

public:

    Rubik_Cube(Rubik *rubik);

    ~Rubik_Cube();

    void start();
};

