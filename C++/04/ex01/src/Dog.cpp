#include "../includes/Dog.hpp"

Dog::Dog(void)
{
    std::cout << "[Dog] Default constructor called" << std::endl;
    this->type = "Dog";
    this->brain = new Brain;
}

Dog::Dog(const Dog &other): Animal(other), brain(new Brain(*other.brain))
{
    std::cout << "[Dog] Copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    if (this != &other)
    {
        std::cout << "[Dog] Copy assignement constructor called" << std::endl;
        Brain *copy = new Brain(*other.brain);

        this->type = other.type;
        delete this->brain;
        this->brain = copy;
    }

    return (*this);
}

Dog::~Dog(void)
{
    std::cout << "[Dog] Destructor called" << std::endl;
    delete this->brain;
}

void Dog::makeSound(void) const
{
    std::cout << "[Dog] Waf" << std::endl;
}