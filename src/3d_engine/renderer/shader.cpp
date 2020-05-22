#include "shader.h"

Shader::Shader(const std::string &vertex_path, const std::string &fragment_path) {
    _id = glCreateProgram();

    GLuint vertex_shader = _compile_shader(
            GL_VERTEX_SHADER,
            vertex_path
    );

    GLuint fragment_shader = _compile_shader(
            GL_FRAGMENT_SHADER,
            fragment_path
    );

    glAttachShader(_id, vertex_shader);
    glAttachShader(_id, fragment_shader);
    glLinkProgram(_id);

    GLint status{0};

    glGetProgramiv(_id, GL_LINK_STATUS, &status);

    if (!status) {
        int length;

        glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

        char *info_log = new char[length];

        glGetProgramInfoLog(_id, length, nullptr, info_log);

        std::string error{info_log};

        delete[] info_log;

        throw std::runtime_error(error);
    }

    glUseProgram(0);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader() {
    glDeleteProgram(_id);
}

std::string Shader::_load_file(const std::string &path) {
    std::ifstream file{path};
    std::string temp;
    std::stringstream source;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + path);
    }

    while (getline(file, temp)) {
        source << temp << '\n';
    }

    file.close();

    return source.str();
}

GLuint Shader::_compile_shader(GLint type, const std::string &file_path) {
    const std::string source = _load_file(file_path);

    GLuint shader_id = glCreateShader(type);
    const GLchar *c_source = source.c_str();

    glShaderSource(shader_id, 1, &c_source, nullptr);
    glCompileShader(shader_id);

    GLint status{0};

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);

    if (!status) {
        int length;

        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

        char *info_log = new char[length];

        glGetShaderInfoLog(shader_id, length, nullptr, info_log);

        std::string error{info_log};

        delete[] info_log;

        throw std::runtime_error(error);
    }

    return shader_id;
}

void Shader::bind() {
    if (_bound) return;

    _bound = true;
    glUseProgram(_id);
}

void Shader::unbind() {
    _bound = false;

    glUseProgram(0);
}

void Shader::set_uniform_matrix_4_fv(const std::string &name, glm::mat4 &matrix) {
    bind();
    glUniformMatrix4fv(
            glGetUniformLocation(_id, name.c_str()),
            1,
            GL_FALSE,
            glm::value_ptr(matrix)
    );
    unbind();
}

void Shader::set_uniform_3_fv(const std::string &name, glm::vec3 &value) {
    bind();
    glUniform3fv(
            glGetUniformLocation(_id, name.c_str()),
            1,
            glm::value_ptr(value)
    );
    unbind();
}

void Shader::set_uniform_1_i(const std::string &name, int value) {
    bind();
    glUniform1i(
            glGetUniformLocation(_id, name.c_str()),
            value
    );
    unbind();
}
