/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 22:52:02 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/31 23:02:02 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>
#include <exception>

class RPN
{
    public:
        RPN(void);
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN(void);

        static void reversePolish(const char *av);
        
        class Error : public std::exception
        {
            public:
                const char *what(void) const throw() { return "Error"; }
        };
};