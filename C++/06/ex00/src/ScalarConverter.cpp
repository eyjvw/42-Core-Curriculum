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
    std::cout << "char: " << c << std::endl
    << "int: " << i << std::endl
    << "float: " << f << std::endl
    << "double: " << d << std::endl;
}

static bool isPseudoLiteral(const std::string &input)
{
    if (input == "nan" || input == "nanf")
        return (printResult("impossible", "impossible", "nanf", "nan"), true);
    if (input == "-inff" || input == "-inf")
        return (printResult("impossible", "impossible", "-inff", "-inf"), true);
    if (input == "+inff" || input == "+inf")
        return (printResult("impossible", "impossible", "+inff", "+inf"), true);
    return (false);
}

// Returns 'c' (char), 'i' (int), 'f' (float), 'd' (double) or 0 if the literal is invalid
static char literalType(const std::string &input)
{
    size_t len = input.length();
    size_t i = 0;
    size_t digits = 0;
    size_t dots = 0;

    if (len == 1 && !isdigit(static_cast<unsigned char>(input[0])))
        return (isprint(static_cast<unsigned char>(input[0])) ? 'c' : 0);
    if (len == 3 && input[0] == '\'' && input[2] == '\'')
        return (isprint(static_cast<unsigned char>(input[1])) ? 'c' : 0);
    if (len > 0 && (input[0] == '+' || input[0] == '-'))
        i++;
    if (len > 0 && input[len - 1] == 'f')
        len--;
    for (; i < len; i++)
    {
        if (isdigit(static_cast<unsigned char>(input[i])))
            digits++;
        else if (input[i] == '.')
            dots++;
        else
            return (0);
    }
    if (digits == 0 || dots > 1)
        return (0);
    if (len != input.length())
        return (dots == 1 ? 'f' : 0);
    return (dots == 1 ? 'd' : 'i');
}

static std::string cStr(const double d)
{
    std::ostringstream temp;
    char c;

    if (d != d || d < 0 || d > 127)
        return ("impossible");
    c = static_cast<char>(d);
    if (!isprint(static_cast<unsigned char>(c)))
        return ("Non displayable");
    temp << "\'" << c << "\'";
    return (temp.str());
}

static std::string iStr(const double d)
{
    std::ostringstream temp;

    if (d != d || d <= static_cast<double>(INT_MIN) - 1.0 || d >= static_cast<double>(INT_MAX) + 1.0)
        return ("impossible");
    temp << static_cast<int>(d);
    return (temp.str());
}

static std::string fStr(const double d)
{
    std::ostringstream temp;
    std::string x;

    if (d != d || d < -FLT_MAX || d > FLT_MAX)
        return ("impossible");
    temp << std::setprecision(6) << static_cast<float>(d);
    x = temp.str();
    if (x.find_first_of(".e") == std::string::npos)
        x += ".0";
    return (x + 'f');
}

static std::string dStr(const double d)
{
    std::ostringstream temp;
    std::string x;

    if (d != d || d < -DBL_MAX || d > DBL_MAX)
        return ("impossible");
    temp << std::setprecision(15) << d;
    x = temp.str();
    if (x.find_first_of(".e") == std::string::npos)
        x += ".0";
    return (x);
}

void ScalarConverter::convert(const std::string input)
{
    char type;
    double d;
    long l;

    if (isPseudoLiteral(input))
        return;
    type = literalType(input);
    if (type == 0)
        return (printResult("impossible", "impossible", "impossible", "impossible"));
    errno = 0;
    if (type == 'c')
        d = static_cast<double>(input.length() == 3 ? input[1] : input[0]);
    else if (type == 'i')
    {
        l = strtol(input.c_str(), NULL, 10);
        if (errno == ERANGE || l < INT_MIN || l > INT_MAX)
            d = strtod(input.c_str(), NULL);
        else
            d = static_cast<double>(static_cast<int>(l));
    }
    else
        d = strtod(input.c_str(), NULL);
    printResult(cStr(d), iStr(d), fStr(d), dStr(d));
}
