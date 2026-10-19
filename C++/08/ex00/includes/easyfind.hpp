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

// Returns an iterator to the first occurrence of value, or container.end() if not found
template <typename T> typename T::iterator easyfind(T &container, int value)
{
    return (std::find(container.begin(), container.end(), value));
}

template <typename T> typename T::const_iterator easyfind(const T &container, int value)
{
    return (std::find(container.begin(), container.end(), value));
}
