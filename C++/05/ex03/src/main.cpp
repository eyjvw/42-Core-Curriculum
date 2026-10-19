/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:41:28 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 01:33:57 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
#include "../includes/AForm.hpp"
#include "../includes/Intern.hpp"
#include "../includes/ShrubberyCreationForm.hpp"

int main(void)
{
    Bureaucrat hoel("hoel", 1);
    Intern randomIntern;
    const std::string names[4] = {"robotomy request", "shrubbery creation", "presidential pardon", "coffee request"};

    for (int i = 0; i < 4; i++)
    {
        AForm* form = NULL;

        try
        {
            form = randomIntern.makeForm(names[i], "Bender");
            hoel.signForm(*form);
            hoel.executeForm(*form);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        delete form;
    }

    return (0);
}
