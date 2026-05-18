/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:45:57 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/25 03:46:34 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/C.hpp"

C::C(void)
{
    std::cout << "[C] Default constructor called" << std::endl;
}

C::C(const C &other)
{
    std::cout << "[C] Copy constructor called" << std::endl;
    (void)other;   
}

C &C::operator=(const C &other)
{
    if (this != &other)
    {
        std::cout << "[C] Copy assignement operator called" << std::endl;
        (void)other;
    }   

    return (*this);
}

C::~C(void)
{
    std::cout << "[C] Destructor called" << std::endl;
}