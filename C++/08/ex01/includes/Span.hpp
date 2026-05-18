/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:28:49 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 22:43:53 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <cstdlib>

class Span
{
    private:
        std::vector<int> data;
        unsigned int N;
    public:
        Span(void);
        Span(unsigned int N);
        Span(const Span &other);
        Span &operator=(const Span &other);
        ~Span(void);

        class TooMuchValues : public std::exception
        {
            public:
                const char *what(void) const throw()
                {
                    return ("This container has already reached his max capacity");
                }
        };

        class CantFind : public std::exception
        {
            public:
                const char *what(void) const throw()
                {
                    return ("Couldn't find value in this container");
                }
        };

        void addNumber(const int nb);
        int shortestSpan(void) const;
        int longestSpan(void) const;      
};