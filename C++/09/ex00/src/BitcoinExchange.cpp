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

BitcoinExchange::BitcoinExchange(std::ifstream &dataBase, const char &limiter)
{
    if (!dataBase.is_open())
        throw(CantOpenFile());

    std::string	line;
    bool firstLine = true;

    while (std::getline(dataBase, line))
    {
        if (firstLine)
        {
            firstLine = false;
            continue;
        }
        
        size_t pos = line.find(limiter);
        
        if (pos == std::string::npos)
        {
            this->container.insert(std::make_pair(line, 0.0f));
            continue ;
        }
        
        std::string date = line.substr(0, pos);
        float value = atof(line.substr(pos + 1).c_str());
        this->container.insert(std::make_pair(date, value));
    }
}

bool BitcoinExchange::isValidDate(std::string line) const
{
    for (size_t i = 0; i < line.size(); i++)
    {
        if (!isdigit(line[i]) && line[i] != '-' && line[i] != ' ')
            return (false);
    }
    
    if (line.find('-') != 4 || line.length() != 11)
        return (false);
    
    int year = atoi(line.substr(0, 4).c_str());
    int month = atoi(line.substr(5, 2).c_str());
    int day = atoi(line.substr(8, 2).c_str());
    
    if (year < 1 || year > 9999 || month < 1 || month > 12 || day < 1)
        return (false);
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    
    if (month == 2 && isLeap)
        daysInMonth[1] = 29;
    
    return (day <= daysInMonth[month - 1]);
}

bool BitcoinExchange::isValidFormat(std::string date, float value) const
{
    if (!isValidDate(date))
    {
        std::cout << WRONGDATE << date << std::endl;
        return (false);
    }

    if (value < 0)
    {
        std::cout << TOOLOW << " => " << value << std::endl;
        return (false);
    }
    
    else if (value > 1000)
    {
        std::cout << TOOLARGE << " => " << value << std::endl;
        return (false);
    }
    
    return (true);
}

time_t BitcoinExchange::dateToTimestamp(const std::string &date)
{
    tm timeinfo = {};
    
    timeinfo.tm_year = atoi(date.substr(0, 4).c_str()) - 1900;
    timeinfo.tm_mon = atoi(date.substr(5, 2).c_str()) - 1;
    timeinfo.tm_mday = atoi(date.substr(8, 2).c_str());
    
    return (timegm(&timeinfo));
}

void	BitcoinExchange::findClosest(t_close &closest, const std::string &itDate, const float &itValue, const std::string &date) const
{
    time_t newDate = dateToTimestamp(itDate);
    time_t actualDate = dateToTimestamp(date);

    if (newDate > actualDate)
        return;
    
    time_t oldDate = dateToTimestamp(closest.date);
    
    if (std::abs(actualDate - oldDate) > std::abs(actualDate - newDate))
    {
        closest.date = itDate;
        closest.value = itValue;
    }
}

void	BitcoinExchange::findExchangeRate(std::string date, float value) const
{
    t_close	closest;
    closest.date = this->container.begin()->first;
    closest.value = this->container.begin()->second;

    for (std::map<std::string, float>::const_iterator itDb = this->container.begin(); itDb != this->container.end(); ++itDb)
    {
        if (itDb->first + ' ' == date)
        {
            std::cout << date << "=> " << value << " = " << value * itDb->second << std::endl;
            return ;
        }
        
        this->findClosest(closest, itDb->first, itDb->second, date);
    }
    
    if (dateToTimestamp(date) < dateToTimestamp(closest.date))
        std::cout << "Error : Bitcoin didn't exist at this date => " << date << std::endl;
    else
        std::cout << date << "=> " << value << " = " << value * closest.value << std::endl;
}

void BitcoinExchange::ExchangeRate(const BitcoinExchange &input) const
{
    for (std::map<std::string, float>::const_iterator itInput = input.container.begin(); itInput != input.container.end(); ++itInput)
    {
        if (this->isValidFormat(itInput->first, itInput->second))
            this->findExchangeRate(itInput->first, itInput->second);
    }
}

void BitcoinExchange::printContent() const {
    for (std::map<std::string, float>::const_iterator it = this->container.begin(); it != this->container.end(); ++it)
        std::cout << it->first << " => " << std::fixed << std::setprecision(2) << it->second << std::endl;
}

