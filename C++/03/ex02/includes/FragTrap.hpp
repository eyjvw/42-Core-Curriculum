#pragma once

#include "ClapTrap.hpp"

#define FRAGTRAP_HIT_POINTS 100
#define FRAGTRAP_ENERGY_POINTS 100
#define FRAGTRAP_ATTACK_DAMAGE 30

class FragTrap : public ClapTrap
{
    public:
        FragTrap(void);
        FragTrap(const std::string name);
        FragTrap(const FragTrap &src);
        FragTrap &operator=(const FragTrap &src);
        ~FragTrap(void);

        void attack(const std::string &target);
        void highFivesGuys(void);
};