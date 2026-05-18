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

static int calculate(int a, int b, char op)
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
    std::stack<int> st;
    std::string input(av);
    
    for (size_t i = 0; i < input.length(); ++i)
    {
        char c = input[i];
        
        if (c == ' ')
            continue;
        
        if (std::isdigit(c))
            st.push(c - '0');
        else if (isOperator(c))
        {
            if (st.size() < 2)
                throw Error();
            
            int b = st.top(); 
            st.pop();
            int a = st.top();
            st.pop();
            
            if (c == '/' && b == 0)
                throw Error();
            st.push(calculate(a, b, c));
        }
        else
            throw Error();
    }
    
    if (st.size() != 1)
        throw Error();
    
    std::cout << st.top() << std::endl;
}