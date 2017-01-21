#include "Point.h"
#include <math.h>

Point::Point(double x_pos, double y_pos)
{
	x = x_pos;
	y = y_pos;
}

Point Point::operator-(const Point & other) const
{
	return Point(x - other.x, y - other.y);
}

double Point::magnitude()
{
	return sqrt(x*x + y*y);
}
