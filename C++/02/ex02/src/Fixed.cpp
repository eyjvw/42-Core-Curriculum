#include "../includes/Fixed.hpp"

Fixed::Fixed(void)
{
    // std::cout << "Default constructor called" << std::endl;
    this->setRawBits(0);
}

Fixed::Fixed(const int raw)
{
    // std::cout << "Int constructor called" << std::endl;
    this->setRawBits(raw << this->bits);
}

Fixed::Fixed(const float raw)
{
    // std::cout << "Float constructor called" << std::endl;
    this->setRawBits(roundf(raw * (1 << this->bits)));
}

Fixed::Fixed(const Fixed& other)
{
    // std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed::~Fixed(void)
{
    // std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    // std::cout << "getRawBits member function called" << std::endl;
    return (this->raw);
}

void Fixed::setRawBits(int raw)
{
    this->raw = raw;
}

int Fixed::toInt(void) const
{
    return (this->raw / (1 << this->bits));
}

float Fixed::toFloat(void) const
{
    return ((float)this->raw / (1 << this->bits));
}

bool		Fixed::operator>(Fixed const &src) const
{
	return (this->raw > src.raw);
}

bool		Fixed::operator<(Fixed const &src) const
{
	return (this->raw < src.raw);
}

bool		Fixed::operator>=(Fixed const &src) const
{
	return (this->raw >= src.raw);
}

bool		Fixed::operator<=(Fixed const &src) const
{
	return (this->raw <= src.raw);
}

bool		Fixed::operator==(Fixed const &src) const
{
	return (this->raw == src.raw);
}

bool		Fixed::operator!=(Fixed const &src) const
{
	return (this->raw != src.raw);
}

Fixed Fixed::operator+(Fixed const &src) const
{
	Fixed res;
	res.setRawBits(this->raw + src.raw);
	return res;
}

Fixed Fixed::operator-(Fixed const &src) const
{
	Fixed res;
	res.setRawBits(this->raw - src.raw);
	return res;
}

Fixed Fixed::operator*(Fixed const &src) const
{
	Fixed res;
	long long product = static_cast<long long>(this->raw) * static_cast<long long>(src.raw);
	res.setRawBits(static_cast<int>(product >> bits));
	return res;
}

Fixed Fixed::operator/(Fixed const &src) const
{
	Fixed res;

	if (src.raw == 0)
	{
		std::cout << "Division can't be done with 0" << std::endl;
		res.setRawBits(0);
		return res;
	}

	long long numerator = static_cast<long long>(this->raw) << bits;
	res.setRawBits(static_cast<int>(numerator / src.raw));
	return res;
}

Fixed &Fixed::operator++(void)
{
	this->raw++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed tmp = *this;
	this->raw++;
	return (tmp);
}

Fixed &Fixed::operator--(void)
{
	this->raw--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed tmp = *this;
	this->raw--;
	return (tmp);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return (a.raw >= b.raw ? a : b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a.raw >= b.raw ? a : b);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return (a.raw <= b.raw ? a : b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a.raw <= b.raw ? a : b);
}

Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
    {
        // std::cout << "Copy assignment operator called" << std::endl;
        this->raw = other.getRawBits();
    }
    
    return *this;
}

std::ostream &operator << (std::ostream &raw, const Fixed &rhs)
{
    raw << rhs.toFloat();
    return (raw);
}