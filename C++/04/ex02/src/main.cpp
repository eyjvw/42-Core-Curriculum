#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/Brain.hpp"

int main(void)
{
    // const Animal *meta = new Animal(); // does not compile: Animal is abstract

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

    std::cout << "\n=== Array of animals ===" << std::endl;

    const int size = 4;
    const Animal *animals[size];

    for (int k = 0;k < size;k++)
    {
        if (k < size / 2)
            animals[k] = new Dog();
        else
            animals[k] = new Cat();
    }
    for (int k = 0;k < size;k++)
        animals[k]->makeSound();
    for (int k = 0;k < size;k++)
        delete animals[k];

    std::cout << "\n=== Deep copy ===" << std::endl;

    Dog basic;
    {
        Dog tmp = basic;
    }
    Cat cat;
    Cat other;
    other = cat;
    std::cout << std::endl;
    
    return (0);
}