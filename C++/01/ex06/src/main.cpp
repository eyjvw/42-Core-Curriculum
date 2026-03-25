/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 03:50:43 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/19 03:53:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac, char **av)
{
    Harl harl;
    std::string level;

    if (ac != 2)
    {
        std::cerr << "You need to pass one argument for Harl to think" << std::endl;
        return (1);
    }

    level = av[1];
    harl.complain(level);
    return (0);
}
