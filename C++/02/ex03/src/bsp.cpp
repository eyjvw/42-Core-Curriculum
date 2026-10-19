#include "../includes/Point.hpp"

// twice the area of the triangle, computed on the raw fixed-point bits
// (exact in a double while the triangle spans less than 2^18 units)
static double get_area(Fixed const a_x, Fixed const b_x, Fixed const c_x, Fixed const a_y, Fixed const b_y, Fixed const c_y)
{
	double ab_x = static_cast<double>(b_x.getRawBits()) - a_x.getRawBits();
	double ab_y = static_cast<double>(b_y.getRawBits()) - a_y.getRawBits();
	double ac_x = static_cast<double>(c_x.getRawBits()) - a_x.getRawBits();
	double ac_y = static_cast<double>(c_y.getRawBits()) - a_y.getRawBits();
	double area = ab_x * ac_y - ac_x * ab_y;

	return (area < 0 ? -area : area);
}

bool bsp(const Point a, const Point b, const Point c, const Point point)
{
	double area = get_area(a.get_x(), b.get_x(), c.get_x(), a.get_y(), b.get_y(), c.get_y());
	double abpoint = get_area(a.get_x(), b.get_x(), point.get_x(), a.get_y(), b.get_y(), point.get_y());
	double acpoint = get_area(a.get_x(), c.get_x(), point.get_x(), a.get_y(), c.get_y(), point.get_y());
	double cbpoint = get_area(c.get_x(), b.get_x(), point.get_x(), c.get_y(), b.get_y(), point.get_y());

	// on an edge or a vertex one of the sub-triangles is flat: not inside
	return (abpoint + acpoint + cbpoint == area && abpoint > 0 && acpoint > 0 && cbpoint > 0);
}