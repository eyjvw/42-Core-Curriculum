/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:40:10 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/25 03:40:30 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

class C : public Base
{
    public:
        C(void);
        C(const C &other);
        C &operator=(const C &other);
        ~C(void);
};