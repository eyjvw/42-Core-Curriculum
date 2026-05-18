#include "../includes/MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	std::cout << "Default Constructor called for MateriaSource" << std::endl;
	for (size_t i = 0; i < 4; i++)
		this->source[i] = NULL;
}

MateriaSource::MateriaSource(MateriaSource const &src)
{
	std::cout << "Copy Constructor called for MateriaSource" << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		if (src.source[i])
			this->source[i]= src.source[i];
		else
			this->source[i] = NULL;
	}
}

void	MateriaSource::operator=(MateriaSource const &src)
{
	std::cout << "Operator assignement called for MateriaSource" << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		if (this->source[i])
		{
			delete this->source[i];
			this->source[i] = NULL;
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (src.source[i])
			this->source[i]= src.source[i];
		else
			this->source[i] = NULL;
	}
}

MateriaSource::~MateriaSource()
{
	std::cout << "Destructor called for MateriaSource" << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		if (this->source[i])
		{
			delete this->source[i];
			this->source[i] = NULL;
		}
	}
}

void	MateriaSource::learnMateria(AMateria *src)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (!this->source[i])
		{
			this->source[i] = src;
			std::cout << "Materia " << src->getType()
			<< " learned at slot " << i << " of MateriaSource inventory" << std::endl;
			return ;
		}
	}
	std::cout << "This MateriaSource is already full" << std::endl;
	delete src;
	return ;
}

AMateria	*MateriaSource::createMateria(std::string const &src)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (this->source[i])
			if (this->source[i]->getType() == src)
				return (this->source[i]->clone());
	}
	if (src == "ice" || src == "cure")
		std::cout << "This MateriaSource have not learned " << src << " yet" << std::endl;
	else
		std::cout << "The Materia " << src << " doesn't exist" << std::endl;
	return (NULL);
}