#include "headers/point3d.hpp"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

Point3d::Point3d(const Point3d &point)
{
    x = point.x;
    y = point.y;
    z = point.z;
}

Point3d::~Point3d()
{
    //cout << "Distructor Point3d" << endl;
}

double Point3d::norm() const
{
    return sqrt(x * x + y * y + z * z);
}

double Point3d::norm_inf() const
{
    return max(abs(x),max( abs(y), abs(z)));
}

void Point3d::to_versor()
{
    double norm = this->norm();
    x = x / norm;
    y = y / norm;
    z = z / norm;
}

Point3d Point3d::operator+(const Point3d &p) const
{
    return Point3d(x + p.x, y + p.y, z + p.z);
}

Point3d Point3d::operator-(const Point3d &p) const
{
    return Point3d(x - p.x, y - p.y, z - p.z);
}

double Point3d::operator*(const Point3d &p) const
{
    return x * p.x + y * p.y + z * p.z;
}

Point3d Point3d::operator*(const double &d) const
{
    return Point3d(x * d, y * d, z * d);
}

Point3d Point3d::x_vect(const Point3d &p) const
{
    double new_x = (y * p.z) - (z * p.y);
    double new_y = (z * p.x) - (x * p.z);
    double new_z = (x * p.y) - (y * p.x);
    return Point3d(new_x, new_y, new_z);
}

void Point3d::matrix_transorm(const Point3d &x1, const Point3d &y1, const Point3d &z1)
{

    double new_x = x * x1.get_x() + y * y1.get_x() + z * z1.get_x();
    double new_y = x * x1.get_y() + y * y1.get_y() + z * z1.get_y();
    double new_z = x * x1.get_z() + y * y1.get_z() + z * z1.get_z();
    x = new_x;
    y = new_y;
    z = new_z;
}

string Point3d::tostring() const
{
    return "Point3d:\nx: " + to_string(x) + " y: " + to_string(y) + " z: " + to_string(z);
}