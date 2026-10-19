#include "../includes/Point.hpp"

Point::Point(void): x(0), y(0) {}
Point::Point(const float x, const float y): x(x), y(y) {}
Point::Point(const Point &src): x(src.x), y(src.y) {}

Fixed Point::get_y(void) const
{
	return(this->y);
}

Fixed Point::get_x(void) const
{
	return(this->x);
}

Point &Point::operator=(const Point &src)
{
	// x and y are const: a Point can not be modified once built
	(void)src;
	return (*this);
}

Point::~Point(void) {}