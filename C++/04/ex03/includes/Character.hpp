#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter
{
    protected:
        std::string	name;
        AMateria	*inv[4];
        AMateria	*ground[1024];
        size_t		idx;
    public:
        Character(void);
        Character(const Character &src);
        void	operator=(const Character &src);
        ~Character(void);

        Character(std::string name);
        std::string const &	getName(void) const;
        void				equip(AMateria *to_equip);
        void				use(int idx, ICharacter& target);
        void				unequip(int idx);
        void				clean_ground(void);
};