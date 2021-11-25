#include "headers/ray.hpp"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

Ray::Ray(Point3d t, Point3d p, bool compute = false)
{
    if (!compute)
    {
        tangent = t;
        tangent.to_versor();
        point = p;
    }
    else
    {
        this->compute_from_points(t, p);
    }
}

Ray::Ray(const Ray &ray)
{
    tangent = ray.tangent;
    point = ray.point;
}

Ray::~Ray()
{
    //cout << "Distructor Ray" << endl;
}

void Ray::compute_from_points(Point3d t, Point3d p)
{
    tangent = (t - p);
    tangent.to_versor();
    point = p;
}

Point3d Ray::get_from_distance(double d) const
{
    Point3d p = tangent * d;
    p = p + point;
    return p;
}

string Ray::tostring() const
{
    return "Ray:\ntan: " + tangent.tostring() + "\npoint: " + point.tostring();
}