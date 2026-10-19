#include "../includes/AMateria.hpp"

AMateria::AMateria()
{
	std::cout << "Default Constructor called for AMateria" << std::endl;
}

AMateria::AMateria(AMateria const &src)
{
	std::cout << "Copy Constructor called for AMateria" << std::endl;
	this->type = src.getType();
}

AMateria	&AMateria::operator=(AMateria const &src)
{
	std::cout << "Operator assignement called for AMateria" << std::endl;
	// the type of a materia never changes: copying it would turn an Ice into a Cure
	(void)src;
	return (*this);
}

AMateria::~AMateria()
{
	std::cout << "Destructor called for AMateria" << std::endl;
}

AMateria::AMateria(std::string const & type)
{
	this->type = type;
}

void AMateria::use(ICharacter& target)
{
	if (this->getType() == "ice")
		std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
	else if (this->getType() == "cure")
		std::cout << "* heals " << target.getName() << "'s wounds *"<< std::endl;
	else
		std::cout << "* Unknown materia used against " << target.getName() << " *" << std::endl;
}

std::string const &AMateria::getType() const
{
	return(this->type);
}