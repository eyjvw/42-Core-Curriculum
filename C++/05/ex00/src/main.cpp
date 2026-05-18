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

    return (0);
}