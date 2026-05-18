/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 03:40:34 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/27 01:14:18 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Base.hpp"
#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"

Base::Base(void)
{
    std::cout << "[Base] Default constructor called" << std::endl;
}

Base::Base(const Base &other)
{
    std::cout << "[Base] Copy constructor called" << std::endl;
    (void)other;   
}

Base &Base::operator=(const Base &other)
{
    if (this != &other)
    {
        std::cout << "[Base] Copy assignement operator called" << std::endl;
        (void)other;
    }   

    return (*this);
}

Base::~Base(void)
{
    std::cout << "[Base] Destructor called" << std::endl;
}

Base *Base::generate(void)
{
    int x = std::rand() % 3;
    Base *base;

    if (x == 0)
        base = new A();
    else if (x == 1)
        base = new B();
    else
        base = new C();
    return (base);
}

void Base::identify(Base *base)
{
    if (dynamic_cast<A*>(base))
    {
        std::cout << "A" << std::endl;
        return;
    }
    if (dynamic_cast<B*>(base))
    {
        std::cout << "B" << std::endl;
        return;
    }
    if (dynamic_cast<C*>(base))
    {
        std::cout << "C" << std::endl;
        return;
    }

    std::cout << "Unknown Type" << std::endl;
}

void Base::identify(Base &base)
{
    try
    {
        (void)dynamic_cast<A&>(base);
        std::cout << "A" << std::endl;
    }
    catch(...)
    {
        try
        {
            (void)dynamic_cast<B&>(base);
            std::cout << "B" << std::endl;
        }
        catch(...)
        {
            try
            {
                (void)dynamic_cast<C&>(base);
                std::cout << "C" << std::endl;
            }
            catch(...)
            {
                std::cout << "Unknown Type" << std::endl;
            }  
        }
    }
}