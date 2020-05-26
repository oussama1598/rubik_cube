#include "rubik_cube.h"

const float EPS = 0.0001f;

Rubik_Cube::Rubik_Cube(Rubik *rubik) : _rubik(rubik) {
    _init_game_engine();
    _init_game_scene();
    _init_cube();
}

Rubik_Cube::~Rubik_Cube() {
    delete _game_engine;
    delete _game_scene;
}


void Rubik_Cube::_init_game_engine() {
    _game_engine = new Engine();

    _game_engine->add_shader(
            "main_shader",
            new Shader(
                    "/home/red-scule/Desktop/projects/cpp_projects/rubik_cube/src/3d_engine/shaders/vertex.glsl",
                    "/home/red-scule/Desktop/projects/cpp_projects/rubik_cube/src/3d_engine/shaders/fragment.glsl"
            )
    );

    _game_engine->add_material(
            "orange",
            new Material{
                    glm::vec3{0.f},
                    glm::vec3{235.f / 255.f, 158.f / 255.f, 54.f / 255.f},
                    glm::vec3{0.f}
            }
    );

    _game_engine->add_material(
            "red",
            new Material{
                    glm::vec3{0.f},
                    glm::vec3{1.f, 0.f, 0.f},
                    glm::vec3{0.f}
            }
    );

    _game_engine->add_material(
            "white",
            new Material{
                    glm::vec3{0.f},
                    glm::vec3{1.f, 1.f, 1.f},
                    glm::vec3{0.f}
            }
    );

    _game_engine->add_material(
            "yellow",
            new Material{
                    glm::vec3{0.f},
                    glm::vec3{255.f / 255.f, 215.f / 255.f, 62.f / 255.f},
                    glm::vec3{0.f}
            }
    );

    _game_engine->add_material(
            "green",
            new Material{
                    glm::vec3{0.f},
                    glm::vec3{0.f, 1.f, 0.f},
                    glm::vec3{0.f}
            }
    );

    _game_engine->add_material(
            "blue",
            new Material{
                    glm::vec3{0.f},
                    glm::vec3{0.f, 0.f, 1.f},
                    glm::vec3{0.f}
            }
    );

    _game_engine->add_material(
            "black",
            new Material{
                    glm::vec3{0.f},
                    glm::vec3{0.f, 0.f, 0.f},
                    glm::vec3{0.f}
            }
    );

    _game_engine->keyboard_controller->set_on_button_clicked([this]() {
        _handle_keyboard_input();
    });

    _game_engine->mouse_controller->set_mouse_handler([this]() {
        _handler_mouse_input();
    });
}

void Rubik_Cube::_init_game_scene() {
    _game_scene = new Scene();

    _game_scene->add_camera(
            new Camera(glm::vec3{0, 0, 8}, {1000, 800})
    );

    _game_engine->add_scene(_game_scene);
}

void Rubik_Cube::_init_cube() {
    Mesh *plane_mesh = new Plane();

    std::map<std::string, Material *> cubie_materials{
            {"orange", _game_engine->get_material("orange")}, // LEFT
            {"red",    _game_engine->get_material("red")},// RIGHT
            {"white",  _game_engine->get_material("white")},// TOP
            {"yellow", _game_engine->get_material("yellow")},// DOWN
            {"green",  _game_engine->get_material("green")},// FRONT
            {"blue",   _game_engine->get_material("blue")}// BACK
    };

    for (auto *cubie_data: _rubik->get_cubies()) {
        glm::vec3 position{cubie_data->get_position()};

        Cubie *cubie = new Cubie(
                position
        );

        for (auto *face_data: cubie_data->get_faces()) {
            Object *face = new Object();
            glm::vec3 face_normal{face_data->get_normal()};

            GLdouble rot =
                    acos(glm::dot(face_data->get_normal(), face_data->get_default_normal())) *
                    180 / M_PI;
            glm::vec3 axis = glm::cross(face_data->get_normal(), face_data->get_default_normal());

            face->translate(position);
            face->translate(face_normal);

            if (glm::dot(axis, axis) > EPS) {
                face->rotate(rot, axis);
            }

            face->scale(glm::vec3{face_data->get_scale()});

            face->set_material(cubie_materials.at(_colors.at(face_data->get_color())));
            face->set_shader(_game_engine->get_shader("main_shader"));
            face->set_mesh(plane_mesh);

            cubie->add_face(face);

            _game_scene->add_object(face);

            _linked_faces.insert({{cubie_data, face_data}, face});
        }
    }
}

void Rubik_Cube::_apply_changes() {
    for (auto &face: _linked_faces) {
        Cubie_Data *cubie_data = face.first.first;
        Face_Data *face_data = face.first.second;
        Object *face_object = face.second;

        face_object->reset_transform();
        glm::vec3 face_normal{face_data->get_normal()};

        GLdouble rot =
                acos(glm::dot(face_data->get_normal(), face_data->get_default_normal())) *
                180 / M_PI;
        glm::vec3 axis = glm::cross(face_data->get_normal(), face_data->get_default_normal());

        face_object->translate(cubie_data->get_position());
        face_object->translate(face_normal);

        if (glm::dot(axis, axis) > EPS) {
            face_object->rotate(rot, axis);
        }

        face_object->scale(glm::vec3{face_data->get_scale()});
    }
}

void Rubik_Cube::_handle_keyboard_input() {
    if (_game_engine->keyboard_controller->is_key_pressed(GLFW_KEY_W)) {
        Camera *camera = _game_scene->get_camera();
        glm::vec3 &camera_front = camera->get_front();
        glm::vec3 direction = camera_front * _game_engine->get_dt();

        camera->translate(direction);
    }

    if (_game_engine->keyboard_controller->is_key_pressed(GLFW_KEY_S)) {
        Camera *camera = _game_scene->get_camera();
        glm::vec3 &camera_front = camera->get_front();
        glm::vec3 direction = -(camera_front * _game_engine->get_dt());

        camera->translate(direction);
    }

    if (_game_engine->keyboard_controller->is_key_pressed(GLFW_KEY_D)) {
        Camera *camera = _game_scene->get_camera();
        glm::vec3 &camera_right = camera->get_right();
        glm::vec3 direction = camera_right * _game_engine->get_dt();

        camera->translate(direction);
    }

    if (_game_engine->keyboard_controller->is_key_pressed(GLFW_KEY_A)) {
        Camera *camera = _game_scene->get_camera();
        glm::vec3 &camera_right = camera->get_right();
        glm::vec3 direction = -(camera_right * _game_engine->get_dt());

        camera->translate(direction);
    }

    if (_game_engine->keyboard_controller->is_key_pressed(GLFW_KEY_F)) {
        _rubik->apply_moves("F");

        _apply_changes();
    }
}

void Rubik_Cube::_handler_mouse_input() {
    float dt = _game_engine->get_dt();

    if (_game_engine->mouse_controller->is_right_button_clicked()) {
        glm::vec2 offset = _game_engine->mouse_controller->get_mouse_offset();
        glm::vec3 rotation{0.f};

        rotation.x -= offset.y * 5.f * dt;
        rotation.y += offset.x * 5.f * dt;

        _game_scene->get_camera()->rotate(rotation);

    }
}

void Rubik_Cube::start() {
    while (_game_engine->running()) {
        _game_engine->render();
    }
}
