#include "../includes/Character.hpp"

Character::Character()
{
	std::cout << "Default Constructor called for Character" << std::endl;
	for (size_t i = 0; i < 4; i++)
		this->inv[i] = NULL;
	this->idx = 0;
}

Character::Character(Character const &src) : ICharacter(src)
{
	std::cout << "Copy Constructor called for Character" << std::endl;
	this->name = src.name;
	this->idx = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (src.inv[i])
			this->inv[i] = src.inv[i]->clone();
		else
			this->inv[i] = NULL;
	}
}

Character	&Character::operator=(Character const &src)
{
	std::cout << "Operator assignement called for Character" << std::endl;
	if (this == &src)
		return (*this);
	this->name = src.name;
	for (size_t i = 0; i < 4; i++)
	{
		if (this->inv[i])
		{
			delete inv[i];
			this->inv[i] = NULL;
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (src.inv[i])
			this->inv[i] = src.inv[i]->clone();
		else
			this->inv[i] = NULL;
	}
	return (*this);
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
	}
	this->idx = 0;
}

AMateria	**Character::find_on_ground(AMateria *m)
{
	for (size_t i = 0; i < this->idx; i++)
	{
		if (this->ground[i] == m)
			return (&this->ground[i]);
	}
	return (NULL);
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
	AMateria	**on_ground;

	if (!to_equip)
		return ;
	for (size_t i = 0; i < 4; i++)
	{
		if (this->inv[i] == to_equip)
		{
			std::cout << "Materia " << to_equip->getType() << " is already equipped by "
			<< this->getName() << std::endl;
			return ;
		}
	}
	on_ground = this->find_on_ground(to_equip);
	for (size_t i = 0; i < 4; i++)
	{
		if (!this->inv[i])
		{
			// picked up from the ground: the ground no longer owns it
			if (on_ground)
				*on_ground = NULL;
			this->inv[i] = to_equip;
			return ;
		}
	}
	std::cout << this->getName() << " Inventory is already full" << std::endl;
	// still owned by the ground when it was dropped there, otherwise nobody owns it
	if (!on_ground)
		delete to_equip;
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx > 3)
		std::cout << "Inventory of " << this->getName() << " Only has 4 slot (0-3)" << std::endl;
	else if (!this->inv[idx])
		std::cout << "Slot : " << idx << " of " << this->getName() << " is empty" << std::endl;
	else
		this->inv[idx]->use(target);
	return;
}

void Character::unequip(int idx)
{
	size_t	slot;

	if (idx < 0 || idx > 3)
		std::cout << "Inventory of " << this->getName() << " Only has 4 slot (0-3)" << std::endl;
	else if (this->inv[idx])
	{
		slot = 0;
		while (slot < this->idx && this->ground[slot])
			slot++;
		if (slot >= GROUND_SIZE)
		{
			std::cout << "The ground of " << this->getName() << " is full, materia "
			<< this->inv[idx]->getType() << " is kept at slot " << idx << std::endl;
			return ;
		}
		std::cout << "Materia " << this->inv[idx]->getType() << " at slot " << idx
		<< " got dropped on the ground by " << this->getName() << std::endl;
		this->ground[slot] = this->inv[idx];
		if (slot == this->idx)
			this->idx++;
		this->inv[idx] = NULL;
	}
	else
		std::cout << "This slot is empty" << std::endl;
}