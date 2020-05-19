#include "engine.h"

Engine::Engine() {
    _window = new Window("Title");
    keyboard_controller = new Keyboard_Controller(_window->get_window());
    mouse_controller = new Mouse_Controller(_window->get_window());

    _gl_setup();
}

Engine::~Engine() {
    for (auto &shader: _shaders) {
        delete shader.second;
    }

    for (auto &material: _materials) {
        delete material.second;
    }

    delete keyboard_controller;
    delete mouse_controller;

    delete _window;
}

void Engine::_gl_setup() {
    glEnable(GL_DEPTH_TEST);

    glFrontFace(GL_CCW);


    // fill shape with color, GL_LINES will only draw the wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // for the alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Engine::_calculate_dt() {
    auto current_time = (float) glfwGetTime();

    _dt = current_time - _last_time;

    _last_time = current_time;
}

void Engine::render() {
    _calculate_dt();

    glfwPollEvents();

    keyboard_controller->update();
    mouse_controller->update();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _scenes[0]->render();

    glfwSwapBuffers(_window->get_window());
    glFlush();

    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
}
