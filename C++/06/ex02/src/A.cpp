/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:42:42 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/25 03:43:13 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/A.hpp"

A::A(void)
{
    std::cout << "[A] Default constructor called" << std::endl;
}

A::A(const A &other)
{
    std::cout << "[A] Copy constructor called" << std::endl;
    (void)other;   
}

A &A::operator=(const A &other)
{
    if (this != &other)
    {
        std::cout << "[A] Copy assignement operator called" << std::endl;
        (void)other;
    }   

    return (*this);
}

A::~A(void)
{
    std::cout << "[A] Destructor called" << std::endl;
}