#include "headers/object.hpp"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

Object::Object()
{
    position = Point3d(0, 0, 0);
    ref_x = Point3d(1, 0, 0);
    ref_y = Point3d(0, 1, 0);
    ref_z = Point3d(0, 0, 1);
}

Object::Object(Point3d p)
{
    position = p;
    ref_x = Point3d(1, 0, 0);
    ref_y = Point3d(0, 1, 0);
    ref_z = Point3d(0, 0, 1);
}

Sphere::Sphere() : Object()
{
    radius = 1;
}

Sphere::Sphere(Point3d p, float r = 1) : Object(p)
{
    radius = r;
}

double Sphere::intersect(const Ray &ray) const
{
    //source wiki line-sphere intersection
    //Ritorna NAN se non c'è intersezione altrimenti d(vedi wiki)
    float delta;
    Point3d u = ray.get_tan();
    u.to_versor();
    Point3d c = position;
    Point3d o = ray.get_point();
    Point3d diff = o - c;
    float p1 = u * diff;
    float p2 = diff.norm();
    delta = (p1 * p1) - (p2 * p2) + (radius * radius);
    //se l'intersezione non esite ritorna NAN
    double res1 = -p1 + sqrt(delta);
    double res2 = -p1 - sqrt(delta);
    // if (abs((u * res1 + diff).norm() - radius) < 0.01 )
    // {
    //     cout << "on sphere" << endl;
    // }
    
    if (abs(res1) < abs(res2))
    {
        return res1;
    }else
    {
        return res2;
    }

}

Point3d Sphere::normal(const Point3d &p) const
{
    Point3d normal = p - position;
    normal.to_versor();
    return normal;
}

Cube::Cube() : Object()
{
    radius = 1;
}

Cube::Cube(Point3d p, float r) : Object(p)
{
    radius = r;
}

double Cube::intersect(const Ray &ray) const
{
    Point3d u = ray.get_tan();
    u.to_versor();
    //centro cubo
    Point3d c = position;
    //origine retta
    Point3d o = ray.get_point();
    Point3d diff = o - c;

    //ci sono 6 Possibilità
    float d[6];
    //soluzioni per componente rispetto a d : |diff +d*u| = r
    d[0] = (-diff.get_x() + radius) / u.get_x();
    d[1] = (-diff.get_x() - radius) / u.get_x();
    d[2] = (-diff.get_y() + radius) / u.get_y();
    d[3] = (-diff.get_y() - radius) / u.get_y();
    d[4] = (-diff.get_z() + radius) / u.get_z();
    d[5] = (-diff.get_z() - radius) / u.get_z();

    float d_min = 10000;
    for (size_t i = 0; i < 6; i++)
    {
        // cout << d[i] << endl;
        //cout << (diff + (u * d[i])).tostring() << endl;
        //cout << (diff + (u * d[i])).norm_inf() << endl;
        if (abs(((u * d[i] + o) - c).norm_inf() - radius) <= 0.0001)
        {
            if (abs(d[i]) < abs(d_min))
            {
                d_min = d[i];
            }
        }
    }
    if (d_min == 10000)
    {
        d_min = NAN;
    }
    return d_min;
}
//calcolo la normale alla faccia indicata del cubo
Point3d Cube::normal(const Point3d &p) const
{
    Point3d normal_s = p - position;
    double a_x = abs(normal_s.get_x());
    double a_y = abs(normal_s.get_y());
    double a_z = abs(normal_s.get_z());
    Point3d normal;
    if (a_x > a_y && a_x > a_z)
    {
        normal.set_x(normal_s.get_x());
        normal.to_versor();
    }
    else if (a_y > a_x && a_y > a_z)
    {
        normal.set_y(normal_s.get_y());
        normal.to_versor();
    }
    else
    {
        normal.set_z(normal_s.get_z());
        normal.to_versor();
    }
    return normal;
}