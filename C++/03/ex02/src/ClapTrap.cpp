#include "../includes/ClapTrap.hpp"

ClapTrap::ClapTrap(void): name("Default"), hit_points(CLAPTRAP_HIT_POINTS), energy_points(CLAPTRAP_ENERGY_POINTS), attack_damage(CLAPTRAP_ATTACK_DAMAGE)
{
    std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string name): name(name), hit_points(CLAPTRAP_HIT_POINTS), energy_points(CLAPTRAP_ENERGY_POINTS), attack_damage(CLAPTRAP_ATTACK_DAMAGE)
{
    std::cout << "ClapTrap name constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &src)
{
    std::cout << "ClapTrap copy constructor called" << std::endl;
    *this = src;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &src)
{
    if (this != &src)
    {
        std::cout << "ClapTrap copy assignement called" << std::endl;

        this->name = src.name;
        this->hit_points = src.hit_points;
        this->energy_points = src.energy_points;
        this->attack_damage = src.attack_damage;
    }

    return (*this);
}

ClapTrap::~ClapTrap(void)
{
    std::cout << "ClapTrap " << this->name << " destructor called" << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
    if (this->hit_points <= 0)
    {
        std::cout << this->name << " is dead" << std::endl;
        return;
    }

    if (this->energy_points <= 0)
    {
        std::cout << "ClapTrap doesn't have enough energy poins to attack" << std::endl;
        return;
    }

    std::cout << "ClapTrap " << this->name << " attacks " << target
        << ", causing " << this->attack_damage << " points of damage !" << std::endl;
    this->energy_points -= 1;
    std::cout << "ClaptTrap " << this->name << " new amount of energy points : " << this->energy_points << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->hit_points <= 0)
    {
        std::cout << "ClapTrap " << this->name << " is dead" << std::endl;
        return;
    }

    std::cout << "ClapTrap " << this->name << " take " << amount << " points of damage" << std::endl;
    this->hit_points -= amount;
    if (this->hit_points < 0)
        this->hit_points = 0;
    std::cout << "ClapTrap " << this->name << " now has " << this->hit_points << " hit points" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->hit_points <= 0)
    {
        std::cout << "ClapTrap : " << this->name << " is dead" << std::endl;
        return;
    }

    if (this->energy_points <= 0)
    {
        std::cout << "ClapTrap doesn't have enough energy points to repair" << std::endl;
        return;
    }

    std::cout << "ClapTrap " << this->name << " repaired " << amount << " points of damage" << std::endl;
    this->hit_points += amount;
    this->energy_points -= 1;
    std::cout << "ClapTrap " << this->name << " new amount of hits points : " << this->hit_points << std::endl;
    std::cout << "ClapTrap " << this->name << " amount of energy points : " << this->energy_points << std::endl;   
}