/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 07:34:04 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 07:41:04 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Iter.hpp"

void printInt(int x)
{
    std::cout << x << " ";
}

void printDouble(double x)
{
    std::cout << x << " ";
}

void printString(std::string str)
{
    std::cout << str << " ";
}

void multiplyByTwo(int &x)
{
    x *= 2;
}

void toUppercase(char &c)
{
    if (c >= 'a' && c <= 'z')
        c = c - 32;
}

void printChar(char c)
{
    std::cout << c << " ";
}

int main(void)
{
    std::cout << "=== Test avec int ===" << std::endl;
    int intArray[] = {1, 2, 3, 4, 5};
    ::iter(intArray, 5, printInt);
    std::cout << std::endl;

    std::cout << "\n=== Test avec double ===" << std::endl;
    double doubleArray[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    ::iter(doubleArray, 5, printDouble);
    std::cout << std::endl;

    std::cout << "\n=== Test avec string ===" << std::endl;
    std::string stringArray[] = {"hello", "world", "cpp"};
    ::iter(stringArray, 3, printString);
    std::cout << std::endl;

    std::cout << "\n=== Test avec modification int ===" << std::endl;
    int modArray[] = {1, 2, 3, 4, 5};
    ::iter(modArray, 5, multiplyByTwo);
    ::iter(modArray, 5, printInt);
    std::cout << std::endl;

    std::cout << "\n=== Test avec char ===" << std::endl;
    char charArray[] = {'a', 'b', 'c', 'd'};
    ::iter(charArray, 4, toUppercase);
    ::iter(charArray, 4, printChar);
    std::cout << std::endl;

    return (0);
}