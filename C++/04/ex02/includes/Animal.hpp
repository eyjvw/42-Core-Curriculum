#pragma once

#include "iostream"

class Animal
{
    protected:
        std::string type;
    public:
        Animal(void);
        Animal(std::string type);
        Animal(const Animal &other);
        Animal &operator=(const Animal &other);
        virtual ~Animal(void);

        std::string getType(void) const;
        virtual void makeSound(void) const = 0;
};