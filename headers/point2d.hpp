#pragma once

#include <iostream>
#include <string>

class Point2d
{
private:
    double x;
    double y;

public:
    double value = 0;
    Point2d() { return; };
    Point2d(double x1, double y1, double v = 0) : x(x1), y(y1), value(v){};
    Point2d(const Point2d &);

    double get_x() const { return x; };
    double get_y() const { return y; };

    void set_x(double x1) { x = x1; };
    void set_y(double y1) { y = y1; };

    double norm() const;

    std::string tostring() const;
};