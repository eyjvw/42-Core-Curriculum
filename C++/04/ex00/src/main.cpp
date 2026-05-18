#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/WrongCat.hpp"

int main(void)
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    const WrongAnimal *k = new WrongCat(); 

    std::cout << "\n=== Normal Test ===" << std::endl;

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    j->makeSound();
    i->makeSound();

    std::cout << "\n=== Wrong Test ===" << std::endl;

    std::cout << k->getType() << " " << std::endl;
    k->makeSound();

    std::cout << std::endl;

    delete meta;
    delete j;
    delete i;
    delete k;

    return (0);
}