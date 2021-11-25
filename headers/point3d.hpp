#pragma once

#include <iostream>
#include <string>

class Point3d
{
private:
    double x;
    double y;
    double z;

public:
    Point3d() : x(0), y(0), z(0){};
    Point3d(double x1, double y1, double z1) : x(x1), y(y1), z(z1){};
    Point3d(const Point3d &);
    ~Point3d();

    double get_x() const { return x; };
    double get_y() const { return y; };
    double get_z() const { return z; };

    void set_x(double x1) { x = x1; };
    void set_y(double y1) { y = y1; };
    void set_z(double z1) { z = z1; };

    double norm() const;
    double norm_inf() const;

    void to_versor();

    Point3d operator+(const Point3d &) const;
    Point3d operator-(const Point3d &) const;
    double operator*(const Point3d &) const;
    Point3d operator*(const double &) const;

    Point3d x_vect(const Point3d &) const;
    void matrix_transorm(const Point3d &, const Point3d &, const Point3d &);

    std::string tostring() const;
};