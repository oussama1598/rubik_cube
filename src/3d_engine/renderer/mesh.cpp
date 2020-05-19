#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex> vertices, const std::vector<GLuint> indices) : _vertices(
        vertices), _indices(indices) {
    _init_vertex_array();
    _init_vertex_buffer();
    _init_elements_buffer();

    _init_attributes();

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}

void Mesh::_init_vertex_array() {
    glCreateVertexArrays(1, &_VAO);

    bind();
}

void Mesh::_init_vertex_buffer() {
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), _vertices.data(),
                 GL_STATIC_DRAW);
}

void Mesh::_init_elements_buffer() {
    glGenBuffers(1, &_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _indices.size(), _indices.data(),
                 GL_STATIC_DRAW);
}

void Mesh::_init_attributes() {
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid *) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid *) offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid *) offsetof(Vertex, texture_coordinates));
    glEnableVertexAttribArray(2);

    // normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);
}

void Mesh::bind() const {
    glBindVertexArray(_VAO);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}

void Mesh::render() {
    bind();

    if (_indices.empty())
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    else
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);

    unbind();
}
