#include "headers/mesh3d.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Mesh3d::Mesh3d(const Mesh3d &mesh)
{
    for (size_t i = 0; i < mesh.points.size(); i++)
    {
        points.push_back(mesh.points[i]);
    }
}

Mesh3d::~Mesh3d()
{
    for (size_t i = 0; i < points.size(); i++)
    {
        delete points[i];
    }
    points.clear();
    //cout << "Distructor Mesh3d" << endl;
}

unsigned int Mesh3d::get_n_points() const
{
    return points.size();
}

const Point3d *Mesh3d::get_point(unsigned int n) const
{
    if (!(n < points.size()))
    {
        return NULL;
    }
    return points[n];
}

void Mesh3d::add_point(Point3d *p)
{
    points.push_back(p);
}

string Mesh3d::tostring() const
{
    return "Mesh3d:\nN_Points: " + to_string(this->get_n_points());
}