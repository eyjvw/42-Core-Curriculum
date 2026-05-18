/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:30:37 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 01:38:38 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Serializer.hpp"

int main(void)
{
    Data test = { .x = 10 };
    uintptr_t raw = Serializer::serialize(&test);
    Data *deserialized = Serializer::deserialize(raw);
    
    std::cout << "[UINTPTR_T] " << raw << std::endl;
    std::cout << "[DATA] " << deserialized->x << std::endl;
    
    return (0);
}