/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 04:14:21 by sbonneau          #+#    #+#             */
/*   Updated: 2026/02/02 01:54:29 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : container(other.container) {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    this->container = other.container;

    return (*this);
}
BitcoinExchange::~BitcoinExchange() {}

static void removeCarriageReturn(std::string &line)
{
    if (!line.empty() && line[line.length() - 1] == '\r')
        line.erase(line.length() - 1);
}

BitcoinExchange::BitcoinExchange(std::ifstream &dataBase)
{
    if (!dataBase.is_open())
        throw(CantOpenFile());

    std::string line;
    bool firstLine = true;
    double value;

    while (std::getline(dataBase, line))
    {
        removeCarriageReturn(line);
        if (firstLine)
        {
            firstLine = false;
            if (line == "date,exchange_rate")
                continue;
        }
        if (line.empty())
            continue;

        if (line.find(',') != 10 || !isValidDate(line.substr(0, 10))
            || !isValidNumber(line.substr(11), value) || value < 0)
            throw(InvalidDataBase());
        this->container[line.substr(0, 10)] = value;
    }
    if (this->container.empty())
        throw(InvalidDataBase());
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return (false);
    for (size_t i = 0; i < date.length(); i++)
    {
        if (i != 4 && i != 7 && !isdigit(static_cast<unsigned char>(date[i])))
            return (false);
    }
    
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    
    if (year < 1 || month < 1 || month > 12 || day < 1)
        return (false);
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    
    if (month == 2 && isLeap)
        daysInMonth[1] = 29;
    
    return (day <= daysInMonth[month - 1]);
}

// Accepts an optional sign, digits and at most one '.', nothing else
bool BitcoinExchange::isValidNumber(const std::string &str, double &value)
{
    size_t i = 0;
    size_t digits = 0;
    bool dot = false;

    if (i < str.length() && (str[i] == '-' || str[i] == '+'))
        i++;
    for (; i < str.length(); i++)
    {
        if (isdigit(static_cast<unsigned char>(str[i])))
            digits++;
        else if (str[i] == '.' && !dot)
            dot = true;
        else
            return (false);
    }
    if (digits == 0)
        return (false);
    value = strtod(str.c_str(), NULL);
    return (true);
}

void BitcoinExchange::isValidFormat(const std::string &line) const
{
    double value;

    if (line.find(" | ") != 10 || !isValidDate(line.substr(0, 10))
        || !isValidNumber(line.substr(13), value))
        std::cout << BADINPUT << line << std::endl;
    else if (value < 0)
        std::cout << TOOLOW << std::endl;
    else if (value > 1000)
        std::cout << TOOLARGE << std::endl;
    else
        this->findExchangeRate(line.substr(0, 10), value);
}

void    BitcoinExchange::findExchangeRate(const std::string &date, double value) const
{
    // First date strictly after the requested one: the previous entry is the closest lower (or equal) date
    std::map<std::string, double>::const_iterator it = this->container.upper_bound(date);

    if (it == this->container.begin())
    {
        std::cout << TOOEARLY << date << std::endl;
        return ;
    }
    --it;
    std::cout << date << " => " << std::setprecision(10) << value << " = " << value * it->second << std::endl;
}

void BitcoinExchange::ExchangeRate(std::ifstream &input) const
{
    std::string line;
    bool firstLine = true;

    while (std::getline(input, line))
    {
        removeCarriageReturn(line);
        if (firstLine)
        {
            firstLine = false;
            if (line == "date | value")
                continue;
        }
        this->isValidFormat(line);
    }
}

const char *BitcoinExchange::CantOpenFile::what() const throw()
{
    return (CANTOPEN);
}

const char *BitcoinExchange::InvalidDataBase::what() const throw()
{
    return (BADDATABASE);
}
