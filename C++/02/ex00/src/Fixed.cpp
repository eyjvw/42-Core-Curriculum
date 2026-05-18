#include "../includes/Fixed.hpp"

Fixed::Fixed(void)
{
    std::cout << "Default constructor called" << std::endl;
    this->setRawBits(0);
}

Fixed::Fixed(int raw)
{
    this->setRawBits(raw);
}

Fixed::Fixed(const Fixed& other)
{
    *this = other;
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->raw);
}

void Fixed::setRawBits(int raw)
{
    this->raw = raw;
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