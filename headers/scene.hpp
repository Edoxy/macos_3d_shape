#include "object.hpp"
#include <iostream>
#include <vector>

class Scene
{
private:
    std::vector<Object *> objects;
    std::vector<Point3d *> lights;

public:
    Scene(){};
    ~Scene();

    unsigned int get_n_obj() const { return objects.size(); };
    Object *get_obj(int) const;
    void add_obj(Object *);
};