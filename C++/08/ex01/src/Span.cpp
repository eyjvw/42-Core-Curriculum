/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:30:44 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 22:45:46 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Span.hpp"

Span::Span(void): N(0) {}

Span::Span(unsigned int N): N(N) {}

Span::Span(const Span &other): data(other.data), N(other.N) {}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        this->data = other.data;
        this->N = other.N;
    }
    
    return (*this);
}

Span::~Span(void) {}

void Span::addNumber(const int nb)
{
    if (this->data.size() >= this->N)
        throw(Span::TooMuchValues());
    this->data.push_back(nb);
}

// The difference of two ints always fits in an unsigned int (computed modulo 2^n, so no overflow)
static unsigned int spanBetween(int a, int b)
{
    return (static_cast<unsigned int>(b) - static_cast<unsigned int>(a));
}

unsigned int Span::shortestSpan() const
{
    if (this->data.size() < 2)
        throw(Span::CantFind());

    std::vector<int> sorted(this->data);
    std::sort(sorted.begin(), sorted.end());

    unsigned int diff = spanBetween(sorted[0], sorted[1]);

    for (size_t i = 2; i < sorted.size(); i++)
    {
        if (spanBetween(sorted[i - 1], sorted[i]) < diff)
            diff = spanBetween(sorted[i - 1], sorted[i]);
    }
        
    return (diff);
}

unsigned int Span::longestSpan() const
{
    if (this->data.size() < 2)
        throw(Span::CantFind());

    int min = *std::min_element(this->data.begin(), this->data.end());
    int max = *std::max_element(this->data.begin(), this->data.end());

    return (spanBetween(min, max));
}

const char *Span::TooMuchValues::what() const throw()
{
    return ("This container has already reached his max capacity");
}

const char *Span::CantFind::what() const throw()
{
    return ("Not enough numbers to find a span");
}
