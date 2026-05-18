#pragma once

#include <iostream>

#define CLAPTRAP_HIT_POINTS 10
#define CLAPTRAP_ENERGY_POINTS 10
#define CLAPTRAP_ATTACK_DAMAGE 0

class ClapTrap
{
    protected:
        std::string name;
        int hit_points;
        unsigned int energy_points;
        unsigned int attack_damage;

    public:
        ClapTrap(void);
        ClapTrap(const std::string name);
        ClapTrap(const ClapTrap &src);
        ClapTrap &operator=(const ClapTrap &src);
        ~ClapTrap(void);

        void attack(const std::string &target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        std::string getName(void);
};