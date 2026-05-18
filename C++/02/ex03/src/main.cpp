#include "../includes/Point.hpp"

int	main(void)
{
	Point a(1, 2);
	Point b(4, 6);
	Point c(5, 1);
	Point point(2, 2);

    if (bsp(a, b, c, point))
        std::cout << "The point is in the triangle" << std::endl;
    else
        std::cout << "The point is not in the triangle" << std::endl;
    return (0);
}