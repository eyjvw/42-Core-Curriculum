/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:12:36 by sbonneau          #+#    #+#             */
/*   Updated: 2026/02/02 01:52:15 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>

#define DBSOURCE "data/data.csv"

#define BADINPUT "Error: bad input => "
#define TOOLARGE "Error: too large a number."
#define CANTOPEN "Error: could not open file."
#define TOOLOW "Error: not a positive number."
#define TOOEARLY "Error: no exchange rate before this date => "
#define BADDATABASE "Error: invalid database."

class BitcoinExchange {
private:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    std::map<std::string, double> container;
public:
    BitcoinExchange(std::ifstream &dataBase);
    ~BitcoinExchange();

    void    ExchangeRate(std::ifstream &input) const;
    void    isValidFormat(const std::string &line) const;
    void    findExchangeRate(const std::string &date, double value) const;

    static bool isValidDate(const std::string &date);
    static bool isValidNumber(const std::string &str, double &value);

    class CantOpenFile : public std::exception {
        public:
            const char* what() const throw();
    };

    class InvalidDataBase : public std::exception {
        public:
            const char* what() const throw();
    };
};
