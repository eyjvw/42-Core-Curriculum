/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:17:01 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 20:20:50 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void): AForm(PresidentialName, PresidentialSignGrade, PresidentialExecGrade)
{
    std::cout << "[PresidentialPardonForm] Default constructor called" << std::endl;
    this->target = "Default";
}

PresidentialPardonForm::PresidentialPardonForm(const std::string target): AForm(PresidentialName, PresidentialSignGrade, PresidentialExecGrade)
{
    std::cout << "[PresidentialPardonForm] Settings constructor called" << std::endl;
    this->target = target;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other): AForm(PresidentialName, PresidentialSignGrade, PresidentialExecGrade)
{
    std::cout << "[PresidentialPardonForm] Copy constructor called" << std::endl;
    this->target = other.target;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
    if (this != &other)
    {
        std::cout << "[PresidentialPardonForm] Copy assignement operator called" << std::endl;
        this->target = other.target;
    }

    return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
    std::cout << "[PresidentialPardonForm] Destructor called" << std::endl;
}

void PresidentialPardonForm::executeForm(void) const
{
    std::cout << this->target << " has been pardoned by Zaphod Beeblebrox" << std::endl;   
}

void PresidentialPardonForm::executeContract(void) const
{
	this->executeForm();
}

std::ostream &operator<<(std::ostream &os, const PresidentialPardonForm &form)
{
    os << "[PresidentialPardonForm] " << form.getName() << std::endl
    << "[PresidentialPardonForm] Is Signed : " << form.getIsSigned() << std::endl
    << "[PresidentialPardonForm] Grade to sign : " << form.getSignGrade() << std::endl
    << "[PresidentialPardonForm] Grade to execute : " << form.getExecGrade() << std::endl;
    
    return (os);
}