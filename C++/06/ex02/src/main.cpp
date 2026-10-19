/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:57:12 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/27 01:10:25 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Base.hpp"

int main(void)
{
    std::srand(std::time(NULL));

    for (int i = 0; i < 5; i++)
    {
        Base *random = generate();
        std::cout << "Object " << i + 1 << ": ";
        identify(random);
        delete random;
    }
    
    for (int i = 0; i < 5; i++)
    {
        Base *random = generate();
        std::cout << "Object " << i + 1 << ": ";
        identify(*random);
        delete random;
    }

    return (0);
}