#include "../includes/Dog.hpp"

Dog::Dog(void)
{
    std::cout << "[Dog] Default constructor called" << std::endl;
    this->type = "Dog";
}

Dog::Dog(const Dog &other)
{
    std::cout << "[Dog] Copy constructor called" << std::endl;
    *this = other;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this != &other)
    {
        std::cout << "[Dog] Copy assignement constructor called" << std::endl;
        this->type = other.type;
    }

    return (*this);
}

Dog::~Dog(void)
{
    std::cout << "[Dog] Destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
    std::cout << "[Dog] Waf" << std::endl;
}