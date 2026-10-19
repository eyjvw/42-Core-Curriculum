#include "../includes/DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void): ClapTrap("Default_clap_name")
{
    std::cout << "DiamondTrap default constructor called" << std::endl;

    this->name = "Default";
    this->hit_points = FRAGTRAP_HIT_POINTS;
    this->energy_points = SCAVTRAP_ENERGY_POINTS;
    this->attack_damage = FRAGTRAP_ATTACK_DAMAGE;
}

DiamondTrap::DiamondTrap(const std::string name): ClapTrap(name + "_clap_name")
{
    std::cout << "DiamondTrap name constructor called" << std::endl;

    this->name = name;
    this->hit_points = FRAGTRAP_HIT_POINTS;
    this->energy_points = SCAVTRAP_ENERGY_POINTS;
    this->attack_damage = FRAGTRAP_ATTACK_DAMAGE;
}

DiamondTrap::DiamondTrap(const DiamondTrap &src): ClapTrap(src), ScavTrap(src), FragTrap(src)
{
    std::cout << "DiamondTrap copy constructor called" << std::endl;
    *this = src;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &src)
{
    if (this != &src)
    {
        std::cout << "DiamondTrap copy assignement called" << std::endl;

        ClapTrap::operator=(src);
        this->name = src.name;
    }

    return (*this);
}

DiamondTrap::~DiamondTrap(void)
{
    std::cout << "DiamondTrap " << this->name << " destructor called " << std::endl;
}

void DiamondTrap::attack(const std::string &target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
	std::cout << "Member function whoAmI called" << std::endl;
	std::cout << "DiamondTrap name : " << this->name << std::endl;
	std::cout << "DiamondTrap clap's name : " << ClapTrap::getName() << std::endl;
}
