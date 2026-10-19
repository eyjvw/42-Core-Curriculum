/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:40:57 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 22:47:17 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Span.hpp"
#include <climits>
#include <cstdlib>
#include <ctime>

int main(void)
{
    Span sp = Span(5);
      
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;

    try
    {
        sp.addNumber(42);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Span small(1);

        small.addNumber(1);
        std::cout << small.shortestSpan() << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    Span copy(sp);
    Span extremes(2);

    extremes.addNumber(INT_MIN);
    extremes.addNumber(INT_MAX);
    std::cout << "copy: " << copy.shortestSpan() << " " << copy.longestSpan() << std::endl;
    std::cout << "extremes: " << extremes.shortestSpan() << " " << extremes.longestSpan() << std::endl;

    std::vector<int> values;
    std::srand(std::time(NULL));
    for (int i = 0; i < 20000; i++)
        values.push_back(std::rand());

    Span big(20000);

    big.addRange(values.begin(), values.end());
    std::cout << "20000 numbers: " << big.shortestSpan() << " " << big.longestSpan() << std::endl;

    try
    {
        big.addRange(values.begin(), values.begin() + 1);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return (0);
}
