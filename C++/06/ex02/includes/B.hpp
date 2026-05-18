/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:39:39 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/25 03:40:02 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

class B : public Base
{
    public:
        B(void);
        B(const B &other);
        B &operator=(const B &other);
        ~B(void);
};