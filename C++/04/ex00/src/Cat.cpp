#include "../includes/Cat.hpp"

Cat::Cat(void)
{
    std::cout << "[Cat] Default constructor called" << std::endl;
    this->type = "Cat";
}

Cat::Cat(const Cat &other)
{
    std::cout << "[Cat] Copy constructor called" << std::endl;
    *this = other;
}

Cat &Cat::operator=(const Cat &other)
{
    if (this != &other)
    {
        std::cout << "[Cat] Copy assignement constructor called" << std::endl;
        this->type = other.type;
    }

    return (*this);
}

Cat::~Cat(void)
{
    std::cout << "[Cat] Destructor called" << std::endl;
}

void Cat::makeSound(void) const
{
    std::cout << "[Cat] Meow" << std::endl;
}