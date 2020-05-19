#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "material.h"
#include "mesh.h"

class Object {
private:
    Shader *_shader{nullptr};
    Material *_material{nullptr};
    Mesh *_mesh{nullptr};

    glm::mat4 _model_matrix;

    glm::vec3 _position{0.f};
    glm::vec3 _rotation{0.f};
    glm::vec3 _scale{1.f};

private:
    void _calculate_model_matrix();

public:
    Object();

    inline void set_shader(Shader *shader) { _shader = shader; }

    inline Shader *get_shader() { return _shader; }

    inline void set_material(Material *material) { _material = material; }

    inline Material *get_material() { return _material; }

    inline void set_mesh(Mesh *mesh) { _mesh = mesh; }

    void move_to(const glm::vec3 &position);

    void rotate(const glm::vec3 &rotation);

    void scale(const glm::vec3 &scale);

    void render();
};

