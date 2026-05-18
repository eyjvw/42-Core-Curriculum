/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 08:01:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 20:47:07 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void): AForm(RobotomyName, RobotomySignGrade, RobotomyExecGrade)
{
    std::cout << "[RobotomyRequestForm] Default constructor called" << std::endl;
    this->target = "Default";
}

RobotomyRequestForm::RobotomyRequestForm(const std::string target): AForm(RobotomyName, RobotomySignGrade, RobotomyExecGrade)
{
    std::cout << "[RobotomyRequestForm] Settings constructor called" << std::endl;
    this->target = target;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other): AForm(RobotomyName, RobotomySignGrade, RobotomyExecGrade)
{
    std::cout << "[RobotomyRequestForm] Copy constructor called" << std::endl;
    this->target = other.target;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
    if (this != &other)
    {
        std::cout << "[RobotomyRequestForm] Copy assignement operator called" << std::endl;
        this->target = other.target;
    }

    return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
    std::cout << "[RobotomyRequestForm] Destructor called" << std::endl;
}

void RobotomyRequestForm::executeForm(void) const
{
    std::cout << "Drilling noises....." << std::endl;
    std::time_t now = std::time(NULL);
    std::tm *localTime = std::localtime(&now);
    
    if (localTime->tm_sec % 2 == 0)
        std::cout << "[RobotomyRequestForm] " << this->target << " robotomy failed." << std::endl;
	else
        std::cout << "[RobotomyRequestForm] " << this->target << " has been robotomized." << std::endl;
}

void RobotomyRequestForm::executeContract(void) const
{
	this->executeForm();
}

std::ostream &operator<<(std::ostream &os, const RobotomyRequestForm &form)
{
    os << "[RobotomyRequestForm] " << form.getName() << std::endl
    << "[RobotomyRequestForm] Is Signed : " << form.getIsSigned() << std::endl
    << "[RobotomyRequestForm] Grade to sign : " << form.getSignGrade() << std::endl
    << "[RobotomyRequestForm] Grade to execute : " << form.getExecGrade() << std::endl;
    
    return (os);
}