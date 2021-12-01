#pragma once
#include <iostream>
#include <vector>
#include "ray.hpp"
#include "plane.hpp"
#include "point2d.hpp"
#include "mesh3d.hpp"
#include "object.hpp"
#include "scene.hpp"

class Camera
{
private:
    Point3d position;
    Point3d normal;
    Point3d oriz;
    Point3d vert;
    const int resolution = 170;

    std::vector<Ray *> light_paths;
    Plane *plane = NULL;
    std::vector<Point2d *> view;

public:
    Camera(){};
    Camera(Point3d);
    Camera(const Camera &);
    ~Camera();

    Point3d get_position() const { return position; };
    Point3d get_normal() const { return normal; };
    Plane *get_plane() const { return plane; };
    Point3d get_oriz() { return oriz; };
    Point3d get_vert() { return vert; };
    Ray *get_light_path(int i) const;
    Point2d *get_view(int i) const;
    int get_n_view() { return view.size(); };

    void push_view(Point2d *p);

    void move(Point3d p) { position = p; };
    void rotate(Point3d);
    void reset();
    void compute_plane();
    void compute_light_path(const Mesh3d &);
    void compute_view();

    void compute_obj_view(const Object &);
    void compute_scene_view(const Scene&);
};