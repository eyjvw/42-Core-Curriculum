#include "../includes/ScavTrap.hpp"

ScavTrap::ScavTrap(void): ClapTrap()
{
    std::cout << "ScavTrap default constructor called" << std::endl;

    this->name = "Default";
    this->hit_points = SCAVTRAP_HIT_POINTS;
    this->energy_points = SCAVTRAP_ENERGY_POINTS;
    this->attack_damage = SCAVTRAP_ATTACK_DAMAGE;
}

ScavTrap::ScavTrap(const std::string name): ClapTrap(name)
{
    std::cout << "ScavTrap name constructor called" << std::endl;

    this->name = name;
    this->hit_points = SCAVTRAP_HIT_POINTS;
    this->energy_points = SCAVTRAP_ENERGY_POINTS;
    this->attack_damage = SCAVTRAP_ATTACK_DAMAGE;
}

ScavTrap::ScavTrap(const ScavTrap &src): ClapTrap(src)
{
    std::cout << "ScavTrap copy constructor called" << std::endl;
    *this = src;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &src)
{
    if (this != &src)
    {
        std::cout << "ScavTrap copy assignement called" << std::endl;

        this->name = src.name;
        this->hit_points = src.hit_points;
        this->energy_points = src.energy_points;
        this->attack_damage = src.attack_damage;
    }

    return (*this);
}

ScavTrap::~ScavTrap(void)
{
    std::cout << "ScavTrap " << this->name << " destructor called" << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
    if (this->hit_points <= 0)
    {
        std::cout << "ScavTrap " << this->name << " is dead" << std::endl;
        return;
    }

    if (this->energy_points <= 0)
    {
        std::cout << "ScavTrap doesn't have enough energy poins to attack" << std::endl;
        return;
    }

    std::cout << "ScavTrap " << this->name << " attacks " << target
        << ", causing " << this->attack_damage << " points of damage !" << std::endl;
    this->energy_points -= 1;
    std::cout << "ScavTrap " << this->name << " new amount of energy points : " << this->energy_points << std::endl;
}

void ScavTrap::guardGate(void)
{
    std::cout << "ScavTrap " << this->name << " is now in Gate keeper mode" << std::endl;
}