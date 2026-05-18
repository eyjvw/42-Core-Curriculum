#include "../includes/Cure.hpp"

Cure::Cure() : AMateria("cure")
{
	std::cout << "Default Constructor called for Cure" << std::endl;
}

Cure::Cure(Cure const &src) : AMateria(src.getType())
{
	std::cout << "Copy Constructor called for Cure" << std::endl;
}

void	Cure::operator=(Cure const &src)
{
	std::cout << "Operator assignement called for Cure" << std::endl;
	this->type = src.getType();
}

Cure::~Cure()
{
	std::cout << "Destructor called for Cure" << std::endl;
}

AMateria	*Cure::clone() const
{
	return(new Cure(*this));
}