#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 _world_up{0.f, 1.f, 0.f};
    glm::vec3 _front{0.f};
    glm::vec3 _right{0.f};
    glm::vec3 _rotation{0.f, -90.f, 0.f};
    glm::vec3 _position{0.f};

    glm::mat4 _projection_matrix{1.f};
    glm::mat4 _view_matrix{1.f};

private:
    void _recalculate_view_matrix();

public:
    Camera(const glm::vec3 &position, const glm::vec2 &size, float field_of_view = 45.f,
           float near_plane = 0.1f,
           float far_plane = 1000.f);

    inline glm::mat4 &get_projection_matrix() { return _projection_matrix; }

    inline glm::mat4 &get_view_matrix() { return _view_matrix; }

    inline glm::vec3 &get_position() { return _position; }

    inline glm::vec3 &get_front() { return _front; }

    inline glm::vec3 &get_right() { return _right; }

    void translate(glm::vec3 &position);

    void rotate(glm::vec3 &rotation);
};

