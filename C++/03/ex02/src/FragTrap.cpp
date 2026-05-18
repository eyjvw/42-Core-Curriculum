#include "../includes/FragTrap.hpp"

FragTrap::FragTrap(void): ClapTrap()
{
    std::cout << "FragTrap default constructor called" << std::endl;

    this->name = "Default";
    this->hit_points = 100;
    this->energy_points = 100;
    this->attack_damage = 30;
}

FragTrap::FragTrap(const std::string name): ClapTrap(name)
{
    std::cout << "FragTrap name constructor called" << std::endl;

    this->name = name;
    this->hit_points = 100;
    this->energy_points = 100;
    this->attack_damage = 30;
}

FragTrap::FragTrap(const FragTrap &src): ClapTrap(src)
{
    std::cout << "FragTrap copy constructor called" << std::endl;
    *this = src;
}

FragTrap &FragTrap::operator=(const FragTrap &src)
{
    if (this != &src)
    {
        std::cout << "FragTrap copy assignement called" << std::endl;

        this->name = src.name;
        this->hit_points = src.hit_points;
        this->energy_points = src.energy_points;
        this->attack_damage = src.attack_damage;
    }

    return (*this);
}

FragTrap::~FragTrap(void)
{
    std::cout << "FragTrap " << this->name << " destructor called" << std::endl;
}

void FragTrap::attack(const std::string &target)
{
    if (this->hit_points <= 0)
    {
        std::cout << "FragTrap " << this->name << " is dead" << std::endl;
        return;
    }

    if (this->energy_points <= 0)
    {
        std::cout << "FragTrap doesn't have enough energy poins to attack" << std::endl;
        return;
    }

    std::cout << "FragTrap " << this->name << " attacks " << target
        << ", causing " << this->attack_damage << " points of damage !" << std::endl;
    this->energy_points -= 1;
    std::cout << "FragTrap " << this->name << " new amount of energy points : " << this->energy_points << std::endl;
}

void FragTrap::highFivesGuys(void)
{
    std::cout << "FragTrap " << this->name << " high-fives ?" << std::endl;
}