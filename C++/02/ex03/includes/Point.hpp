#pragma once

#include "Fixed.hpp"

class Point
{
    private:
        const Fixed x;
        const Fixed y;
    public:
        Point(void);
        Point(const float x, const float y);
        Point(const Point &other);
        Point operator=(const Point &other);
        ~Point(void);
        
        Fixed get_x(void) const;
        Fixed get_y(void) const;
};

bool bsp(const Point a, const Point b, const Point c, const Point point);