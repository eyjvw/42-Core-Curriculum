/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:05:34 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 07:29:13 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Bureaucrat;

class Form
{
    private:
        const std::string name;
        const int signGrade;
        const int execGrade;
        bool isSigned;
    public:
        Form(void);
        Form(const std::string name, const int signGrade, const int execGrade);
        Form(const Form &other);
        Form &operator=(const Form &other);
        ~Form(void);

        class GradeTooHighException : public std::exception
        {
            public:
                const char *what() const throw()
                {
                    return ("Grade too high for the form");
                }
        };

        class GradeTooLowExecption : public std::exception
        {
            public:
                const char *what() const throw()
                {
                    return ("Grade to low for the form");
                }
        };

        const std::string &getName(void) const;
        int getSignGrade(void) const;
        int getExecGrade(void) const;
        bool getIsSigned(void) const;
        void beSigned(const Bureaucrat &bureaucrat);
};

std::ostream &operator<<(std::ostream &os, const Form &form);