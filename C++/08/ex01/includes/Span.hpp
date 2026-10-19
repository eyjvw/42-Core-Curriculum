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
#include <algorithm>
#include <iterator>

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
                const char *what(void) const throw();
        };

        class CantFind : public std::exception
        {
            public:
                const char *what(void) const throw();
        };

        void addNumber(const int nb);
        template <typename It> void addRange(It begin, It end);
        unsigned int shortestSpan(void) const;
        unsigned int longestSpan(void) const;
};

template <typename It>
void Span::addRange(It begin, It end)
{
    if (static_cast<size_t>(std::distance(begin, end)) > this->N - this->data.size())
        throw(Span::TooMuchValues());
    this->data.insert(this->data.end(), begin, end);
}
