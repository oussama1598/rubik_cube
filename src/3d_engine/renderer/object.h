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

    glm::mat4 _model_matrix{1.f};

public:
    Object() = default;

    inline void set_shader(Shader *shader) { _shader = shader; }

    inline Shader *get_shader() { return _shader; }

    inline void set_material(Material *material) { _material = material; }

    inline Material *get_material() { return _material; }

    inline void set_mesh(Mesh *mesh) { _mesh = mesh; }

    void reset_transform();

    void translate(const glm::vec3 &direction);

    void rotate(float angle, const glm::vec3 &axis);

    void scale(const glm::vec3 &scale);

    void render();
};

