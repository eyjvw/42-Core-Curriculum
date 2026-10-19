/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:35:21 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 20:45:56 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Intern.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"

Intern::Intern(void)
{
    std::cout << "[Intern] Default constructor called" << std::endl;
}

Intern::Intern(const Intern &other)
{
    (void)other;
    std::cout << "[Intern] Copy constructor called" << std::endl;
}

Intern &Intern::operator=(const Intern &other)
{
    if (this != &other)
    {
        std::cout << "[Intern] Assignement operator called" << std::endl;
    }

    return (*this);
}

Intern::~Intern(void)
{
    std::cout << "[Intern] Destructor called" << std::endl;
}

static AForm *createPresidential(const std::string &target)
{
    return new PresidentialPardonForm(target);
}

static AForm *createRobotomy(const std::string &target)
{
    return new RobotomyRequestForm(target);
}

static AForm *createShrubbery(const std::string &target)
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::makeForm(const std::string formName, const std::string targetName) const
{
    const std::string names[3] = {"presidential pardon", "robotomy request", "shrubbery creation"};
    AForm *(*creators[3])(const std::string &) = {&createPresidential, &createRobotomy, &createShrubbery};

    for (int i = 0; i < 3; i++)
    {
        if (formName == names[i])
        {
            AForm *form = creators[i](targetName);

            std::cout << "Intern creates " << form->getName() << std::endl;
            return (form);
        }
    }
    throw Intern::InvalidForm();
}

const char *Intern::InvalidForm::what() const throw()
{
    return ("This form doesn't exist");
}
