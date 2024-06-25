#include "Point.hpp"

/*
** ------------------------- CONSTRUCTOR & DESTRUCTOR --------------------------
*/
Point::Point(): _x(0), _y(0) {}

Point::Point(const float f1, const float f2)
    : _x(f1), _y(f2) {}

Point::Point(const Point& pt) 
    : _x(pt.getX()), _y(pt.getY()) {}

Point::~Point() {}

/*
** ------------------------- PRIVATE OVERLOADS --------------------------
*/
Point& Point::operator=(const Point& rhs) 
{  
    (void)rhs;
    return *this; 
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/
// getters
const Fixed&    Point::getX() const { return _x; }
const Fixed&    Point::getY() const { return _y; }
float           Point::getXVal() const { return _x.toFloat(); }
float           Point::getYVal() const { return _y.toFloat(); }