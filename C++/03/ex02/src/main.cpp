#include "../includes/FragTrap.hpp"
#include "../includes/ScavTrap.hpp"

int main(void)
{
    FragTrap shrek("Shrek");
    
    shrek.beRepaired(0);
    shrek.attack("Fiona");
    shrek.highFivesGuys();

    std::cout << std::endl;
    {
        ScavTrap donkey("Donkey");

        donkey.attack("Dragon");
        donkey.takeDamage(30);
        donkey.guardGate();
    }
    std::cout << std::endl;

    ClapTrap *traps[2];

    traps[0] = new FragTrap("Puss");
    traps[1] = new ScavTrap("Gingy");
    for (int i = 0;i < 2;i++)
        traps[i]->attack("Farquaad");
    for (int i = 0;i < 2;i++)
        delete traps[i];
    std::cout << std::endl;

    return (0);
}