#include "../includes/WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void): type("WrongAnimal")
{
    std::cout << "[WrongAnimal] Default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type): type(type)
{
    std::cout << "[WrongAnimal] Type constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other)
{
    std::cout << "[WrongAnimal] Copy constructor called" << std::endl;
    *this = other;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other)
{
    if (this != &other)
    {
        std::cout << "[WrongAnimal] Copy assignement constructor called" << std::endl;
        this->type = other.type;
    }

    return (*this);
}

WrongAnimal::~WrongAnimal(void)
{
    std::cout << "[WrongAnimal] Destructor called" << std::endl;
}

std::string WrongAnimal::getType(void) const
{
    return (this->type);
}

void WrongAnimal::makeSound(void) const
{
    std::cout << "[WrongAnimal] WrongAnimal make sound" << std::endl;
}