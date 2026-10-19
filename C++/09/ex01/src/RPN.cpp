/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 22:55:07 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/31 23:03:51 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN &other)
{
    (void)other;
}

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return (*this);
}

RPN::~RPN(void) {}

static bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*');
}

static long calculate(long a, long b, char op)
{
    switch (op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

void RPN::reversePolish(const char *av)
{
    std::stack<long, std::list<long> > st;
    std::string input(av);
    
    for (size_t i = 0; i < input.length(); ++i)
    {
        char c = input[i];
        
        if (std::isspace(static_cast<unsigned char>(c)))
            continue;
        
        // Every token is a single character separated by spaces
        if (i + 1 < input.length() && !std::isspace(static_cast<unsigned char>(input[i + 1])))
            throw Error();
        if (std::isdigit(static_cast<unsigned char>(c)))
            st.push(c - '0');
        else if (isOperator(c))
        {
            if (st.size() < 2)
                throw Error();
            
            long b = st.top(); 
            st.pop();
            long a = st.top();
            st.pop();
            
            if (c == '/' && b == 0)
                throw Error();

            long result = calculate(a, b, c);

            if (result < INT_MIN || result > INT_MAX)
                throw Error();
            st.push(result);
        }
        else
            throw Error();
    }
    
    if (st.size() != 1)
        throw Error();
    
    std::cout << st.top() << std::endl;
}

const char *RPN::Error::what() const throw()
{
    return ("Error");
}
