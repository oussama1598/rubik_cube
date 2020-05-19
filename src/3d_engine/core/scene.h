#pragma once

#include <vector>

#include "../renderer/camera.h"
#include "../renderer/shader.h"
#include "../renderer/object.h"

class Scene {
private:
    std::vector<Camera *> _cameras;
    std::vector<Object *> _objects;

public:
    Scene();

    ~Scene();

    void add_camera(Camera *camera);

    inline Camera *get_camera() { return _cameras[0]; }

    void add_object(Object *object);

    void render();
};

