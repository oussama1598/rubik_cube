#pragma once

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
    GLuint _id;
    bool _bound{false};

private:
    std::string _load_file(const std::string &path);

    GLuint _compile_shader(GLint type, const std::string &file_path);

public:

    Shader(const std::string &vertex_path, const std::string &fragment_path);

    ~Shader();

    void bind();

    void unbind();

    void set_uniform_matrix_4_fv(const std::string &name, glm::mat4 &matrix);

    void set_uniform_3_fv(const std::string &name, glm::vec3 &value);
};

