/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 01:05:34 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 07:49:44 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Bureaucrat;

class AForm
{
    protected:
        std::string target;
    private:
        const std::string name;
        const int signGrade;
        const int execGrade;
        bool isSigned;
    public:
        AForm(void);
        AForm(const std::string name, const int signGrade, const int execGrade);
        AForm(const AForm &other);
        AForm &operator=(const AForm &other);
        virtual ~AForm(void);

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
        
        class CantExecute : public std::exception
        {
            public:
                const char* what() const throw()
                {
                    return ("Can't execute the contract because the executer rank is too low");
                }
        };
        
        class NotSigned : public std::exception
        {
            public:
                const char* what() const throw()
                {
                    return ("Can't execute the contract because it's not signed");
                }
        };

        const std::string &getName(void) const;
        int getSignGrade(void) const;
        int getExecGrade(void) const;
        bool getIsSigned(void) const;
        void execute(const Bureaucrat &bureaucrat) const;
        void beSigned(const Bureaucrat &bureaucrat);
        virtual void executeContract(void) const = 0;
};

std::ostream &operator<<(std::ostream &os, const AForm &form);