#include "headers/display.hpp"
#include <iostream>
#include <cstdio>
#include <cstring>

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
        if (p->value > 0.96)
        {
            c = '%';
        }
        else if (p->value > 0.8)
        {
            c = '#';
        }
        else if (p->value > 0.6)
        {
            c = '@';
        }
        else if (p->value > 0.3)
        {
            c = '*';
        }else if (p->value > 0)
        {
            c = '+';
        }
        else
        {
            c = '.';
        }
        window[y][x] = c;
    }
    // Use a single buffer to write entire frame at once
    static char buffer[100000];
    int pos = 0;
    
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = 0; j < dim; j++)
        {
            buffer[pos++] = window[i][j];
            buffer[pos++] = ' ';
        }
        buffer[pos++] = '\n';
    }
    buffer[pos] = '\0';
    fwrite(buffer, 1, pos, stdout);
    fflush(stdout);
}