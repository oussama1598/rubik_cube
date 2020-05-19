#include "scene.h"

Scene::Scene() {

}

Scene::~Scene() {
    for (Camera *camera: _cameras) {
        delete camera;
    }
}


void Scene::add_camera(Camera *camera) {
    _cameras.push_back(camera);
}

void Scene::add_object(Object *object) {
    _objects.push_back(object);
}


void Scene::render() {
    for (Object *object: _objects) {
        Shader *shader = object->get_shader();
        Material *material = object->get_material();

        shader->set_uniform_matrix_4_fv("projection_matrix", _cameras[0]->get_projection_matrix());
        shader->set_uniform_matrix_4_fv("view_matrix", _cameras[0]->get_view_matrix());

        material->attach_to_shader(shader);

//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        object->render();

//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        object->render();
    }
}
