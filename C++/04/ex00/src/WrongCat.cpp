#include "../includes/WrongCat.hpp"

WrongCat::WrongCat(void)
{
    std::cout << "[WrongCat] Default constructor called" << std::endl;
    this->type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat &other)
{
    std::cout << "[WrongCat] Copy constructor called" << std::endl;
    *this = other;
}

WrongCat &WrongCat::operator=(const WrongCat &other)
{
    if (this != &other)
    {
        std::cout << "[WrongCat] Copy assignement constructor called" << std::endl;
        this->type = other.type;
    }

    return (*this);
}

WrongCat::~WrongCat(void)
{
    std::cout << "[WrongCat] Destructor called" << std::endl;
}

void WrongCat::makeSound(void) const
{
    std::cout << "[WrongCat] Meow" << std::endl;
}