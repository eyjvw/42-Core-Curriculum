/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 06:43:16 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 07:46:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/AForm.hpp"
#include "../includes/Bureaucrat.hpp"

AForm::AForm(void): name("Default"), signGrade(150), execGrade(150), isSigned(false)
{
    std::cout << "[AForm] Default constructor called" << std::endl;
}

AForm::AForm(const std::string name, const int signGrade, const int execGrade): name(name), signGrade(signGrade), execGrade(execGrade), isSigned(false)
{
    if (signGrade < 1 || execGrade < 1)
        throw AForm::GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw AForm::GradeTooLowException();
    std::cout << "[AForm] Settings constructor called" << std::endl;
}

AForm::AForm(const AForm &other): name(other.getName()), signGrade(other.getSignGrade()), execGrade(other.getExecGrade()), isSigned(other.getIsSigned())
{
    std::cout << "[AForm] Copy constructor called" << std::endl;
}

AForm &AForm::operator=(const AForm &other)
{
    if (this != &other)
    {
        std::cout << "[Form] Copy assignement operator called" << std::endl;
        this->isSigned = other.isSigned;
    }

    return (*this);
}

AForm::~AForm(void)
{
    std::cout << "[AForm] Destructor called" << std::endl;
}

const std::string &AForm::getName(void) const
{
    return (this->name);
}

int AForm::getSignGrade(void) const
{
    return (this->signGrade);
}

int AForm::getExecGrade(void) const
{
    return (this->execGrade);
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > this->signGrade)
        throw AForm::GradeTooLowException();
    this->isSigned = true;
}

bool AForm::getIsSigned(void) const
{
    return (this->isSigned);
}

std::ostream &operator<<(std::ostream &os, const AForm &form)
{
    os << "[AForm] " << form.getName() << std::endl
    << "[AForm] Is Signed : " << form.getIsSigned() << std::endl
    << "[AForm] Grade to sign : " << form.getSignGrade() << std::endl
    << "[AForm] Grade to execute : " << form.getExecGrade() << std::endl;
    
    return (os);
}

void AForm::execute(const Bureaucrat &bureaucrat) const
{
    if (!this->isSigned)
        throw AForm::NotSigned();
    if (bureaucrat.getGrade() > this->execGrade)
        throw AForm::CantExecute();
    this->executeContract();
}

const char *AForm::GradeTooHighException::what() const throw()
{
    return ("Grade too high for the form");
}

const char *AForm::GradeTooLowException::what() const throw()
{
    return ("Grade too low for the form");
}

const char *AForm::CantExecute::what() const throw()
{
    return ("Can't execute the contract because the executer rank is too low");
}

const char *AForm::NotSigned::what() const throw()
{
    return ("Can't execute the contract because it's not signed");
}
