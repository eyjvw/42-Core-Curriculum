#pragma once

#include <iostream>

class Brain
{
    private:
        std::string ideas[100];
    public:
        Brain(void);
        Brain(Brain const &other);
        Brain &operator=(const Brain &other);
        ~Brain(void);

        void fillIdeas(std::string idea);
        const std::string &getIdeas(size_t i) const;
};