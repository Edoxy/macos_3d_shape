#pragma once
#include "camera.hpp"

class Display
{
private:
    const static int dim = 170;
    const int sleep = 20;
    char window[dim][dim];

public:
    Display();

    void setup(){};
    void clear();
    void draw(Camera &);
};