/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:48:53 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 21:51:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/easyfind.hpp"

int main(void)
{
    std::vector<int> vec;
    
    for (int i = 0;i <= 100;i++)
    {
        vec.push_back(i);
    }

    easyfind(vec, 101);
    easyfind(vec, 100);

    return (0);
}