#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

#define GROUND_SIZE 1024

class Character : public ICharacter
{
    protected:
        std::string	name;
        AMateria	*inv[4];
        AMateria	*ground[GROUND_SIZE];
        size_t		idx;

        AMateria	**find_on_ground(AMateria *m);
    public:
        Character(void);
        Character(const Character &src);
        Character	&operator=(const Character &src);
        ~Character(void);

        Character(std::string name);
        std::string const &	getName(void) const;
        void				equip(AMateria *to_equip);
        void				use(int idx, ICharacter& target);
        void				unequip(int idx);
        void				clean_ground(void);
};