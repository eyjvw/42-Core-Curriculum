/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:44:57 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/25 03:45:48 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/B.hpp"

B::B(void)
{
    std::cout << "[B] Default constructor called" << std::endl;
}

B::B(const B &other)
{
    std::cout << "[B] Copy constructor called" << std::endl;
    (void)other;   
}

B &B::operator=(const B &other)
{
    if (this != &other)
    {
        std::cout << "[B] Copy assignement operator called" << std::endl;
        (void)other;
    }   

    return (*this);
}

B::~B(void)
{
    std::cout << "[B] Destructor called" << std::endl;
}