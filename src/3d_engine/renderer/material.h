#pragma once

#include <glm/glm.hpp>

#include "shader.h"

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    void attach_to_shader(Shader *shader) {
        shader->set_uniform_3_fv("material.diffuse", diffuse);
    }
};
