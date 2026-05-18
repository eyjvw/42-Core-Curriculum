#include "../includes/Animal.hpp"

Animal::Animal(void): type("Animal")
{
    std::cout << "[Animal] Default constructor called" << std::endl;
}

Animal::Animal(std::string type): type(type)
{
    std::cout << "[Animal] Type constructor called" << std::endl;
}

Animal::Animal(const Animal &other)
{
    std::cout << "[Animal] Copy constructor called" << std::endl;
    *this = other;
}

Animal &Animal::operator=(const Animal &other)
{
    if (this != &other)
    {
        std::cout << "[Animal] Copy assignement constructor called" << std::endl;
        this->type = other.type;
    }

    return (*this);
}

Animal::~Animal(void)
{
    std::cout << "[Animal] Destructor called" << std::endl;
}

std::string Animal::getType(void) const
{
    return (this->type);
}