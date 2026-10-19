#pragma once

#include "AMateria.hpp"

#include <iostream>

class Ice : public AMateria
{
    public:
        Ice(void);
        Ice(Ice const &src);
        Ice	&operator=(Ice const &src);
        ~Ice(void);

        AMateria	*clone(void) const;
};