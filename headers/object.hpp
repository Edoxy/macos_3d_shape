#pragma once
#include "point3d.hpp"
#include "ray.hpp"

class Object
{
protected:
    Point3d position;
    Point3d ref_x;
    Point3d ref_y;
    Point3d ref_z;

public:
    Object();
    Object(Point3d);

    Point3d get_pos() const { return position; };
    void set_pos(Point3d p) { position = p; };
    void set_ref(Point3d, Point3d, Point3d);
    virtual double intersect(const Ray &) const = 0;
    virtual Point3d normal(const Point3d &) const = 0;
};

class Sphere : public Object
{
private:
    float radius;

public:
    Sphere();
    Sphere(Point3d, float);
    Sphere(const Sphere &);

    float get_radius() const { return radius; };
    void set_radius(float r) { radius = r; };
    double intersect(const Ray &) const;
    Point3d normal(const Point3d &) const;
};

class Cube : public Object
{
private:
    float radius;

public:
    Cube();
    Cube(Point3d, float);
    Cube(const Cube &);

    double intersect(const Ray &) const;
    Point3d normal(const Point3d &) const;
};

class Square : public Object
{
private:
    float radius;
    
public:
    Square();
    Square(Point3d, float);
    Square(const Square&);

    double intersect(const Ray &) const;
    Point3d normal(const Point3d &) const;
};