/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:43:59 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 07:30:01 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Form.hpp"
#include "../includes/Bureaucrat.hpp"

Form::Form(void): name("Default"), signGrade(150), execGrade(150)
{
    std::cout << "[Form] Default constructor called" << std::endl;
}

Form::Form(const std::string name, const int signGrade, const int execGrade): name(name), signGrade(signGrade), execGrade(execGrade), isSigned(false)
{
    std::cout << "[Form] Settings constructor called" << std::endl;
}

Form::Form(const Form &other): name(other.getName()), signGrade(other.getSignGrade()), execGrade(other.getExecGrade())
{
    std::cout << "[Form] Copy constructor called" << std::endl;
}

Form &Form::operator=(const Form &other)
{
    if (this != &other)
    {
        std::cout << "[Form] Copy assignement operator called" << std::endl;
        this->isSigned = other.isSigned;
    }

    return (*this);
}

Form::~Form(void)
{
    std::cout << "[Form] Destructor called" << std::endl;
}

const std::string &Form::getName(void) const
{
    return (this->name);
}

int Form::getSignGrade(void) const
{
    return (this->signGrade);
}

int Form::getExecGrade(void) const
{
    return (this->execGrade);
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > this->signGrade)
        throw Form::GradeTooLowExecption();
    this->isSigned = true;
}

bool Form::getIsSigned(void) const
{
    return (this->isSigned);
}

std::ostream &operator<<(std::ostream &os, const Form &form)
{
    os << "[Form] " << form.getName() << std::endl
    << "[Form] Is Signed : " << form.getIsSigned() << std::endl
    << "[Form] Grade to sign : " << form.getSignGrade() << std::endl
    << "[Form] Grade to execute : " << form.getExecGrade() << std::endl;
    
    return (os);
}