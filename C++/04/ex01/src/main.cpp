#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/Brain.hpp"

int main(void)
{
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << std::endl;
    std::cout << j->getType() << std::endl;
    std::cout << i->getType() << std::endl;
    std::cout << std::endl;

    j->makeSound();
    i->makeSound();

    std::cout << std::endl;
    
    delete j;
    delete i;
    
    return (0);
}