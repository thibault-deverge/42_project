#pragma once

#include <iostream>
#include "Fixed.hpp"

class Point
{
private:
    const Fixed _x;
    const Fixed _y;

    Point& operator=(const Point& rhs);
public:
    // Constructors/destructor
    Point();
    Point(const float f1, const float f2);
    Point(const Point& point);
    ~Point();

    // Accessers
    const Fixed& getX() const;
    const Fixed& getY() const;
    float    getXVal() const;
    float    getYVal() const;
};

bool bsp(const Point a, const Point b, const Point c, const Point point);