/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 07:27:31 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 07:29:05 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdint.h>

template <typename T> void swap(T &a, T &b)
{
    T temp = a;

    a = b;
    b = temp;
}

template <typename T> T &min(T &a, T &b)
{
    if (b <= a)
        return (b);
    else
        return (a);
}

template <typename T> T &max(T &a, T &b)
{
    if (b >= a)
        return (b);
    else
        return (a);
}