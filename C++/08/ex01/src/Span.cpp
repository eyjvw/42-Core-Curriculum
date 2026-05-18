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

Span::Span(const Span &other): N(other.N)
{
    for (size_t i = 0;i < this->N;i++)
        this->data[i] = other.data[i];
}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        this->N = other.N;

        for (size_t i = 0;i < this->N;i++)
            this->data[i] = other.data[i];
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

int Span::shortestSpan() const
{
    if (this->data.size() < 2)
        throw(Span::CantFind());

    int	diff = abs(this->data[0] - this->data[1]);

    for (size_t i = 0; i < this->data.size(); i++)
    {
        for (size_t j = i + 1; j < this->data.size(); j++)
        {
            if (diff > abs(this->data[i] - this->data[j]))
                diff = abs(this->data[i] - this->data[j]);
        }
    }
        
    return (diff);
}

int Span::longestSpan() const
{
    if (this->data.size() < 2)
        throw(Span::CantFind());

    int	diff = abs(this->data[0] - this->data[1]);
    
    for (size_t i = 0; i < this->data.size(); i++)
    {
        for (size_t j = i + 1; j < this->data.size(); j++)
        {
            if (diff < abs(this->data[i] - this->data[j]))
                diff = abs(this->data[i] - this->data[j]);
        }
    }
        
    return (diff);
}