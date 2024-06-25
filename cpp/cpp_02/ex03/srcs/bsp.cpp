#include "Point.hpp"

static float checkPoint(const Point& a, const Point& b, const Point& pt)
{
    return ((a.getXVal()- pt.getXVal()) * (b.getYVal() - pt.getYVal()) 
            - (a.getYVal() - pt.getYVal()) * (b.getXVal() - pt.getXVal()));
}

bool bsp(const Point a, const Point b, const Point c, const Point point)
{
    float aire1 = checkPoint(c, a, point);
    float aire2 = checkPoint(a, b, point);
    float aire3 = checkPoint(b, c, point);

    if ((aire1 > 0 && aire2 > 0 && aire3 > 0)
        || (aire1 < 0 && aire2 < 0 && aire3 < 0))
        return true;
    return false;
}