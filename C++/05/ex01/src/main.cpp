/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:59:27 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 01:27:17 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bureaucrat.hpp"
#include "../includes/Form.hpp"

int main(void)
{
    Form testForm("testForm", 1, 1);
    
    try
    {
        Bureaucrat hoel("Hoel", 11);

        std::cout << "[Bureaucrat] Name " << hoel.getName() << std::endl; 
        std::cout << "[Bureaucrat] Grade " << hoel.getGrade() << std::endl;
        
        hoel.decrementGrade();
        hoel.decrementGrade();
        hoel.signForm(testForm);
        
        std::cout << hoel << std::endl;
        std::cout << testForm << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return (0);
}