#include "../includes/ClapTrap.hpp"


int main(void)
{
	ClapTrap shrek("Shrek");

	shrek.beRepaired(5);
	
	for (int i = 0;i < 5;i++)
	{
		shrek.attack("Marge");
	}

	for (int i = 0;i < 5;i++)
	{
		shrek.takeDamage(1);
	}

	return (0);
}