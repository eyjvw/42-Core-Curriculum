#pragma once

#include "ClapTrap.hpp"

#define SCAVTRAP_HIT_POINTS 100
#define SCAVTRAP_ENERGY_POINTS 50
#define SCAVTRAP_ATTACK_DAMAGE 20

class ScavTrap : public ClapTrap
{
    public:
        ScavTrap(void);
        ScavTrap(const std::string name);
        ScavTrap(const ScavTrap &src);
        ScavTrap &operator=(const ScavTrap &src);
        ~ScavTrap(void);

        void attack(const std::string &target);
        void guardGate(void);
};