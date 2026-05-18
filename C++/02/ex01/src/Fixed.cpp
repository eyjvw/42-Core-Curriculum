#include "../includes/Fixed.hpp"

Fixed::Fixed(void)
{
    std::cout << "Default constructor called" << std::endl;
    this->setRawBits(0);
}

Fixed::Fixed(const int raw)
{
    std::cout << "Int constructor called" << std::endl;
    this->setRawBits(raw << this->bits);
}

Fixed::Fixed(const float raw)
{
    std::cout << "Float constructor called" << std::endl;
    this->setRawBits(roundf(raw * (1 << this->bits)));
}

Fixed::Fixed(const Fixed& other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    // std::cout << "getRawBits member function called" << std::endl;
    return (this->raw);
}

void Fixed::setRawBits(int const raw)
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

Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
    {
        std::cout << "Copy assignment operator called" << std::endl;
        this->raw = other.getRawBits();
    }
    
    return *this;
}

std::ostream &operator << (std::ostream &raw, const Fixed &rhs)
{
    raw << rhs.toFloat();
    return (raw);
}