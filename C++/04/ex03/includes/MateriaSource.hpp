#pragma once

#include "IMateriaSource.hpp"
#include <iostream>

class MateriaSource : public IMateriaSource
{
    protected:
        AMateria	*source[4];
    public:
        MateriaSource(void);
        MateriaSource(const MateriaSource &src);
        void	operator=(const MateriaSource &src);
        ~MateriaSource(void);

        void		learnMateria(AMateria* src);
        AMateria*	createMateria(const std::string &src);
};