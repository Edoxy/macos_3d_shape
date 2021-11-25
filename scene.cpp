#include "headers/scene.hpp"

Scene::~Scene()
{
    for(size_t i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
    for(size_t i = 0; i < lights.size(); i++)
    {
        delete lights[i];
    }
    objects.clear();
    lights.clear();
}

Object* Scene::get_obj(int n) const
{
    return objects[n];
}

void Scene::add_obj(Object* obj)
{
    objects.push_back(obj);
}