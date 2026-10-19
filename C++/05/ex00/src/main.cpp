/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:59:27 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 01:24:35 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat hoel("Hoel", 1);

        std::cout << "[Bureaucrat] Name " << hoel.getName() << std::endl; 
        std::cout << "[Bureaucrat] Grade " << hoel.getGrade() << std::endl;
        
        hoel.decrementGrade();
        hoel.decrementGrade();
        
        std::cout << hoel << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat tooHigh("TooHigh", 0);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat tooLow("TooLow", 151);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat top("Top", 1);

        top.incrementGrade();
    }
    catch(const Bureaucrat::GradeTooHighException &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat bottom("Bottom", 150);
        Bureaucrat copy(bottom);

        std::cout << copy << std::endl;
        bottom.decrementGrade();
    }
    catch(const Bureaucrat::GradeTooLowException &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}