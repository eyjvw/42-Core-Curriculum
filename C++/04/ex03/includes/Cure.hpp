#pragma once

#include "AMateria.hpp"

#include <iostream>

class Cure : public AMateria
{
    public:
        Cure(void);
        Cure(const Cure &src);
        void	operator=(const Cure &src);
        ~Cure();

        AMateria	*clone(void) const;
};