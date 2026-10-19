/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:41:28 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 01:30:59 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
#include "../includes/AForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/PresidentialPardonForm.hpp"

int main(void)
{
    Bureaucrat hoel("hoel", 1);
    Bureaucrat intern("intern", 150);
    AForm* forms[3];

    forms[0] = new ShrubberyCreationForm("test");
    forms[1] = new RobotomyRequestForm("Bender");
    forms[2] = new PresidentialPardonForm("Arthur Dent");

    for (int i = 0; i < 3; i++)
    {
        hoel.executeForm(*forms[i]);
        intern.signForm(*forms[i]);
        hoel.signForm(*forms[i]);
        intern.executeForm(*forms[i]);
        hoel.executeForm(*forms[i]);
    }
    for (int i = 0; i < 3; i++)
        hoel.executeForm(*forms[1]);

    for (int i = 0; i < 3; i++)
        delete forms[i];
    return (0);
}
