#pragma once
class Point
{
public:
	Point(double x_pos, double y_pos);
	~Point() = default;
	Point operator-(const Point& other) const;
	double magnitude();
	double x, y;
};

