/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:37:57 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/27 01:12:52 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstdlib>

class Base
{
    public:
        Base(void);
        Base(const Base &other);
        Base &operator=(const Base &other);
        virtual ~Base(void);

        Base *generate(void);
        void identify(Base *p);
        void identify(Base &p);
};