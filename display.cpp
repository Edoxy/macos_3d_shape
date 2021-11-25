#include "headers/display.hpp"
#include <iostream>

Display::Display()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            window[i][j] = ' ';
        }
    }
}

void Display::clear()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            window[i][j] = ' ';
        }
    }
}

void Display::draw(Camera &cam)
{
    for (size_t i = 0; i < cam.get_n_view(); i++)
    {
        Point2d *p = cam.get_view(i);
        int x = int(round(p->get_x() * dim));
        int y = int(round(p->get_y() * dim));
        char c;
        if (p->value > 0.95)
        {
            c = '%';
        }
        else if (p->value > 0.7)
        {
            c = '#';
        }
        else if (p->value > 0.3)
        {
            c = '@';
        }
        else if (p->value > -0.1)
        {
            c = '*';
        }else if (p->value > -0.6)
        {
            c = '+';
        }
        else
        {
            c = '.';
        }
        window[y][x] = c;
    }
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = 0; j < dim; j++)
        {
            std::cout << window[i][j] << " ";
        }
        std::cout << std::endl;
    }
}