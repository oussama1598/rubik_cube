#pragma once

#include <vector>

#include <GL/glew.h>
#include "vertex.h"

class Mesh {
private:
    GLuint _VAO;
    GLuint _VBO;
    GLuint _EBO;

    std::vector<Vertex> _vertices;

    std::vector<GLuint> _indices;
private:

    void _init_vertex_array();

    void _init_vertex_buffer();

    void _init_elements_buffer();

    static void _init_attributes();

public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

    ~Mesh();

    void bind() const;

    static void unbind();

    void render();
};

