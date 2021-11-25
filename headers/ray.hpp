#pragma once
#include "point3d.hpp"
#include <string>

class Ray
{
private:
    Point3d tangent;
    Point3d point;

public:
    Ray(){};
    Ray(Point3d, Point3d, bool);
    Ray(const Ray &);
    ~Ray();

    void set_tan(Point3d t) { tangent = t; t.to_versor(); };
    void set_point(Point3d p) { point = p; };

    Point3d get_tan() const { return tangent; };
    Point3d get_point() const { return point; };

    void compute_from_points(Point3d, Point3d);
    Point3d get_from_distance(double) const;

    std::string tostring() const;
};