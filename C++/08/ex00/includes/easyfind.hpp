/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:46:06 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 21:51:19 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T> bool easyfind(T &container, int value)
{
    std::cout << "Value : " << value;

    if (std::find(container.begin(), container.end(), value) != container.end())
    {
        std::cout << " found in container" << std::endl;
        return (true);
    }

    std::cout << " not found in container" << std::endl;
    return (false);
}

