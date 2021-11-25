#include <iostream>
#include <math.h>
#include "headers/plane.hpp"
#include "headers/point3d.hpp"
#include "headers/ray.hpp"

using namespace std;

Plane::Plane(Point3d n, Point3d p)
{
    normal = n;
    point = p;
}

Plane::Plane(const Plane &p)
{
    normal = p.normal;
    point = p.point;
}

Plane::~Plane()
{
    //cout << "Distructor Plane" << endl;
}

Point3d *Plane::compute_intersection(const Ray &r) const
{
    const float TOLL = 0.1;
    Point3d u = r.get_tan();
    if (abs(u * normal) > TOLL)
    {
        Point3d P0 = r.get_point();
        Point3d w = P0 - point;
        double S1 = -(normal * w) / (normal * u);
        double x = u.get_x() * S1 + P0.get_x();
        double y = u.get_y() * S1 + P0.get_y();
        double z = u.get_z() * S1 + P0.get_z();
        return new Point3d(x, y, z);
    }
    else
    {
        return NULL; //null pointer if there are no intersections or there is but very distant
    }
}