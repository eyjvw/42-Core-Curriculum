#include "../includes/DiamondTrap.hpp"

int main(void)
{
    DiamondTrap shrek("Shrek");

    shrek.beRepaired(5);
    shrek.guardGate();

    for (int i = 0;i < 51;i++)
    {
        shrek.attack("Lenny Auvray");
    }

    shrek.highFivesGuys();
    shrek.whoAmI();

    return (0);
}