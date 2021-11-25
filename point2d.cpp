#include "headers/point2d.hpp"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

Point2d::Point2d(const Point2d &point)
{
    x = point.x;
    y = point.y;
}

double Point2d::norm() const
{
    return sqrt(x * x + y * y);
}

string Point2d::tostring() const
{
    return "Point2d:\nx: " + to_string(x) + " y: " + to_string(y);
}