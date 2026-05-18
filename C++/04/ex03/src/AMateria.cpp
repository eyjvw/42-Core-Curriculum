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

void	AMateria::operator=(AMateria const &src)
{
	std::cout << "Operator assignement called for AMateria" << std::endl;
	this->type = src.getType();
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
		std::cout << "* shoots an ice bolt at " << target.getName() << std::endl;
	else if (this->getType() == "cure")
		std::cout << "* heals " << target.getName() << "'s wounds *"<< std::endl;
	else
		std::cout << "* Unknow materia used agaisnt " << target.getName() << " *" << std::endl;
}

std::string const &AMateria::getType() const
{
	return(this->type);
}