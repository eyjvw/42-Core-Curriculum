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

AForm* Intern::makeForm(const std::string formName, const std::string targetName) const
{
    if (formName == "PresidentialPardonForm")
        return new PresidentialPardonForm(targetName);
    if (formName == "RobotomyRequestForm")
        return new RobotomyRequestForm(targetName);
    if (formName == "ShrubberyCreationForm")
        return new ShrubberyCreationForm(targetName);
    throw Intern::InvalidForm();
}

