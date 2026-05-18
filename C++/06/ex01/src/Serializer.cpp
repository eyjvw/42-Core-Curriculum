/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:27:09 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/25 03:30:33 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Serializer.hpp"

Serializer::Serializer(void)
{
    std::cout << "[Serializer] Default constructor called" << std::endl;
}

Serializer::Serializer(const Serializer &other)
{
    std::cout << "[Serializer] Copy constructor called" << std::endl;
    (void)other;
}

Serializer &Serializer::operator=(const Serializer &other)
{
    if (this != &other)
    {
        std::cout << "[Serializer] Copy assignement operator called" << std::endl;
    }
    
    return (*this);
}

Serializer::~Serializer(void)
{
    std::cout << "[Serializer] Destructor called" << std::endl;
}

uintptr_t Serializer::serialize(Data *ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data *>(raw);
}