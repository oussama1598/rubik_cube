#pragma once

#include <functional>
#include <map>

#include "window.h"
#include "../renderer/shader.h"
#include "../renderer/material.h"
#include "scene.h"
#include "mouse_controller.h"
#include "keyboard_controller.h"

class Engine {
private:
    Window *_window;

    std::map<std::string, Shader *> _shaders;
    std::map<std::string, Material *> _materials;
    std::vector<Scene *> _scenes;


    float _dt{0};
    float _last_time{0};

private:
    void _gl_setup();

    void _calculate_dt();

public:
    Mouse_Controller *mouse_controller;
    Keyboard_Controller *keyboard_controller;

public:

    Engine();

    ~Engine();

    inline bool running() { return !glfwWindowShouldClose(_window->get_window()); }

    inline void add_shader(const std::string &shader_name, Shader *shader) {
        _shaders.insert({shader_name, shader});
    }

    inline Shader *get_shader(const std::string &name) { return _shaders.at(name); }

    inline void add_material(const std::string &name, Material *material) {
        _materials.insert({name, material});
    }

    inline Material *get_material(const std::string &name) { return _materials.at(name); }

    inline void add_scene(Scene *scene) { _scenes.push_back(scene); }

    inline float get_dt() { return _dt; }

    void render();
};

