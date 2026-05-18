#include "../includes/Point.hpp"

float get_area(Fixed const a_x, Fixed const b_x, Fixed const c_x, Fixed const a_y, Fixed const b_y, Fixed const c_y)
{
	return (0.5f * std::abs(a_x.toFloat() * (b_y.toFloat() - c_y.toFloat()) + b_x.toFloat() * (c_y.toFloat() - a_y.toFloat()) + c_x.toFloat() * (a_y.toFloat() - b_y.toFloat())));
}

bool bsp(const Point a, const Point b, const Point c, const Point point)
{
	float area = get_area(a.get_x(), b.get_x(), c.get_x(), a.get_y(), b.get_y(), c.get_y());
	float abpoint = get_area(a.get_x(), b.get_x(), point.get_x(), a.get_y(), b.get_y(), point.get_y());
	float acpoint = get_area(a.get_x(), c.get_x(), point.get_x(), a.get_y(), c.get_y(), point.get_y());
	float cbpoint = get_area(c.get_x(), b.get_x(), point.get_x(), c.get_y(), b.get_y(), point.get_y());

	float total = abpoint + acpoint + cbpoint;
	const float epsilon = 1e-6f;
	
	return (std::abs(total - area) < epsilon && abpoint > epsilon && acpoint > epsilon && cbpoint > epsilon);
}