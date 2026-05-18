#pragma once

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

#define FRAGTRAP_HIT_POINTS 100
#define FRAGTRAP_ENERGY_POINTS 100
#define FRAGTRAP_ATTACK_DAMAGE 30 

class DiamondTrap : public ScavTrap, public FragTrap
{
    private:
        std::string name;
    public:
        DiamondTrap(void);
        DiamondTrap(const std::string name);
        DiamondTrap(const DiamondTrap &src);
        DiamondTrap &operator=(const DiamondTrap &src);
        ~DiamondTrap(void);

        using ScavTrap::attack;
        void whoAmI();
};