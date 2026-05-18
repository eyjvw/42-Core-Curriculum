#pragma once

#include <iostream>

#define HIT_POINTS 10
#define ENERGY_POINTS 10
#define ATTACK_DAMAGE 0

class ClapTrap
{
    private:
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
};