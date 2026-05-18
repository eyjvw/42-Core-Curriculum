#pragma once

#include <iostream>
#include "ICharacter.hpp"

class AMateria
{
    protected:
        std::string	type;
    public:
        AMateria(void);
        AMateria(AMateria const &src);
        void	operator=(AMateria const &src);
        virtual ~AMateria(void);

        AMateria(std::string const & type);
        std::string const & getType(void) const;
        virtual AMateria* clone(void) const = 0;
        virtual void use(ICharacter& target);
};