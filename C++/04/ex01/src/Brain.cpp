#include "../includes/Brain.hpp"

Brain::Brain(void)
{
    std::cout << "[Brain] Default constructor called" << std::endl;
}

Brain::Brain(const Brain &other)
{
    std::cout << "[Brain] Copy constructor called" << std::endl;
    *this = other;
}

Brain &Brain::operator=(const Brain &other)
{
    if (this != &other)
    {
        std::cout << "[Brain] Copy assignement constructor called" << std::endl;
        
        for (size_t i = 0;i < 100;i++)
            this->ideas[i] = other.ideas[i];
    }

    return (*this);
}

Brain::~Brain(void)
{
    std::cout << "[Brain] Destructor called" << std::endl;
}

void Brain::fillIdeas(std::string idea)
{
    for (size_t i = 0;i < 100;i++)
        this->ideas[i] = idea;
}

const std::string &Brain::getIdeas(size_t i) const
{
    return (this->ideas[i]);
}