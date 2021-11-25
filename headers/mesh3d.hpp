#pragma once
#include "point3d.hpp"
#include <vector>

class Mesh3d
{
private:
    std::vector<Point3d *> points;

public:
    Mesh3d(){};
    Mesh3d(const Mesh3d &);
    ~Mesh3d();

    unsigned int get_n_points() const;
    const Point3d *get_point(unsigned int) const;
    
    void add_point(Point3d *);

    std::string tostring() const;
};