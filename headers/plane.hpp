#pragma once
#include <iostream>
#include <math.h>
#include "point3d.hpp"
#include "ray.hpp"
#include <string>

class Plane
{
private:
    Point3d normal;
    Point3d point;

public:
    Plane(){};
    Plane(Point3d, Point3d);
    Plane(const Plane &);
    ~Plane();

    Point3d get_normal() const { return normal; };
    Point3d get_point() const { return point; };

    void set_normal(const Point3d &n) { normal = n; };

    Point3d *compute_intersection(const Ray &) const;

    std::string tostring() const;
};