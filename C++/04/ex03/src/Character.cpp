#include "../includes/Character.hpp"

Character::Character()
{
	std::cout << "Default Constructor called for Character" << std::endl;
	for (size_t i = 0; i < 4; i++)
		this->inv[i] = NULL;
	this->idx = 0;
	this->ground[this->idx] = NULL;
}

Character::Character(Character const &src)
{
	std::cout << "Copy Constructor called for Character" << std::endl;
	this->name = src.name;
	this->idx = src.idx;
	this->ground[this->idx + 1] = NULL;
	for (size_t i = 0; i < 4; i++)
	{
		if (src.inv[i])
			this->inv[i] = src.inv[i];
		else
			this->inv[i] = NULL;
	}
}

void	Character::operator=(Character const &src)
{
	std::cout << "Operator assignement called for Character" << std::endl;
	this->name = src.name;
	for (size_t i = 0; i < 4; i++)
	{
		if (this->inv[i])
		{
			delete inv[i];
			this->inv[i] = NULL;
		}
	}
	this->clean_ground();
	this->idx = src.idx;
	this->ground[this->idx + 1] = NULL;
	for (size_t i = 0; i < 4; i++)
	{
		if (src.inv[i])
			this->inv[i] = src.inv[i];
		else
			this->inv[i] = NULL;
	}
}

Character::~Character()
{
	std::cout << "Destructor called for Character " << this->getName() << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		if (this->inv[i])
		{
			delete inv[i];
			this->inv[i] = NULL;
		}
	}
	this->clean_ground();
}

void	Character::clean_ground()
{
	std::cout << "Cleaning the item dropped on the ground by "
	<< this->getName() << std::endl;
	for (size_t i = 0; i < this->idx; i++)
	{
		if (this->ground[i])
		{
			delete ground[i];
			this->ground[i] = NULL;
		}
		else
			break ;
	}
}

Character::Character(std::string name)
{
	std::cout << "Name Constructor called for Character" << std::endl;
	this->name = name;
	this->idx = 0;
	for (size_t i = 0; i < 4; i++)
		this->inv[i] = NULL;
}

std::string const &Character::getName() const
{
	return (this->name);
}

void	Character::equip(AMateria *to_equip)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (!this->inv[i])
		{
			this->inv[i] = to_equip;
			return ;
		}
	}
	std::cout << this->getName() << " Inventory is already full" << std::endl;
	delete to_equip;
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx > 3)
		std::cout << "Inventory of " << this->getName() << " Only has 4 slot (0-3)" << std::endl;
	else if (!this->inv[idx])
		std::cout << "Slot : " << idx << " of " << this->getName() << " is empty" << std::endl;
	else if (idx < 0 || idx > 3)
		std::cout << "Inventory of " << this->getName() << " Only has 4 slot (0-3)" << std::endl;
	else
		this->inv[idx]->use(target);
	return;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx > 3)
		std::cout << "Inventory of " << this->getName() << " Only has 4 slot (0-3)" << std::endl;
	else if (this->inv[idx])
	{
		std::cout << "Materia " << this->inv[idx]->getType() << " at slot " << idx
		<< " got dropped on the ground by " << this->getName() << std::endl;
		this->ground[this->idx] = this->inv[idx];
		this->idx++;
		this->ground[this->idx] = NULL;
		this->inv[idx] = NULL;
	}
	else
		std::cout << "This slot is empty" << std::endl;
}