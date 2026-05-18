/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:04:14 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/23 00:00:38 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{
    std::cout << "[ScalarConverter] Default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    (void)other;
    std::cout << "[ScalarConverter] Copy constructor called" << std::endl;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    if (this != &other)
    {
        std::cout << "[ScalarConverter] Assignement operator called" << std::endl;
    }

    return (*this);
}

ScalarConverter::~ScalarConverter(void)
{
    std::cout << "[ScalarConverter] Destructor called" << std::endl;
}

static void printResult(std::string c, std::string i, std::string f, std::string d)
{
    std::cout << "char : " << c << std::endl
    << "int : " << i << std::endl
    << "float : " << f << std::endl
    << "double : " << d << std::endl;
}

static bool correctArgs(const std::string &input)
{
    size_t i = 0;
    size_t len = input.length();

    if (len == 1)
        return (isprint(static_cast<unsigned char>(input[0])));
    if (input == "nan" || input == "nanf")
        return (printResult("impossible", "impossible", "nanf", "nan"), false);
    if (input == "-inff" || input == "-inf")
        return (printResult("impossible", "impossible", "-inff", "-inf"), false);
    if (input == "+inff" || input == "+inf")
        return (printResult("impossible", "impossible", "+inff", "+inf"), false);
    while (i < len && !isdigit(static_cast<unsigned char>(input[i])))
        i++;
    return (i < len);
}

static std::string cStr(const char c, const int i)
{
    std::ostringstream temp;
    std::string x;

    if (i < 0 || i > 127)
        return ("impossible");
    if (!isprint(i))
        return ("Non displayable");
    temp << "\'" << c << "\'";
    x = temp.str();
    return x;
}

static std::string iStr(const int toInt, const double d)
{
    std::ostringstream temp;
    std::string i;

    if (d < INT_MIN || d > INT_MAX)
        return ("impossible");
    else
    {
        temp << toInt;
        i = temp.str();
        return (i);
    }
}

static std::string fStr(const float f, const double d)
{
	std::ostringstream temp;
	std::string x;

    if (d < -FLT_MAX || d > FLT_MAX)
		return ("impossible");
	else
	{
		temp << std::setprecision(6) << f;
		x = temp.str();
		if (x.find('.') == std::string::npos)
			x += ".0f";
		else
			x += 'f';
		return (x);
	}
}

static std::string dStr(const double d)
{
	std::ostringstream temp;
	std::string x;

	temp << std::setprecision(15) << d;
	x = temp.str();
	if (x.find('.') == std::string::npos)
		x += ".0";
	return (x);
}

void ScalarConverter::convert(const std::string input)
{
    size_t len = input.length();
    char c = 0;
    int i = 0;
    float f = 0;
    double d = 0;
    long tempInt = 0;
    long double tempDouble = 0;
        
    if (!correctArgs(input))
        return;
    if (len == 1 && isalpha(input[0]))
    {
        c = input[0];
        i = static_cast<int>(c);
        f = static_cast<float>(c);
        d = static_cast<double>(c);
    }
    else if (input[len - 1] == 'f')
    {
        tempDouble = atof(input.c_str());
        
        if ((tempDouble < FLT_MIN || tempDouble > FLT_MAX) && tempDouble != 0)
        {
            std::cerr << "Float overflow" << std::endl;
            return;
        }
    
        f = atof(input.c_str());
        c = static_cast<char>(f);
        i = static_cast<int>(f);
        d = static_cast<double>(f);
    }
    else if (input.find('.') != std::string::npos)
    {
        tempDouble = strtold(input.c_str(), NULL);
        
        if (tempDouble < DBL_MIN || tempDouble > DBL_MAX)
        {
            std::cerr << "Double overflow" << std::endl;
            return;
        }

        d = atof(input.c_str());
        i = static_cast<int>(d);
        c = static_cast<char>(d);
        f = static_cast<float>(d);
    }
    else
    {
        tempInt = atol(input.c_str());
        
        if (tempInt < INT_MIN || tempInt > INT_MAX)
        {
            std::cerr << "Int overflow" << std::endl;
            return;
        }
        
        i = atoi(input.c_str());
        c = static_cast<char>(i);
        f = static_cast<float>(i);
        d = static_cast<double>(i);
    }
    
    printResult(cStr(c, i), iStr(i, d), fStr(f, d), dStr(d));
}