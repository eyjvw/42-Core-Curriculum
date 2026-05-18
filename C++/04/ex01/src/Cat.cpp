#include "../includes/Cat.hpp"

Cat::Cat(void)
{
    std::cout << "[Cat] Default constructor called" << std::endl;
    this->type = "Cat";
    this->brain = new Brain;
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
        delete this->brain;
        this->brain = new Brain(*other.brain);
    }

    return (*this);
}

Cat::~Cat(void)
{
    std::cout << "[Cat] Destructor called" << std::endl;
    delete this->brain;
}

void Cat::makeSound(void) const
{
    std::cout << "[Cat] Meow" << std::endl;
}