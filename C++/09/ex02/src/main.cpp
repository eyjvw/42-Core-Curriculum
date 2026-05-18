/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 01:36:07 by sbonneau          #+#    #+#             */
/*   Updated: 2026/02/01 03:12:33 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/PmergeMe.hpp"

int main(int ac, char **av)
{
    PmergeMe mergeMe;

    if (!mergeMe.checkArgs(ac, av))
        return (1);
    if (!mergeMe.hasNoDup(ac, av))
        return (1);
    
    mergeMe.initVector(ac, av);
    mergeMe.start();

    return (0);
}
