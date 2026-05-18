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
#include <algorithm>
#include <map>
#include <fstream>
#include <iomanip>
#include <ctime>

#define DBSOURCE "data/data.csv"

#define NEGATIVEVALUE "Error not a positive number."
#define BADINPUT "Error: bad input."
#define TOOLARGE "Error: too large a number."
#define VALUENOTFOUND "Error: missing value"
#define CANTOPEN "Error: could not open file."
#define WRONGFORMAT "Error: invalid format (<date> | <value>)."
#define WRONGDATE "Error: bad input => "
#define TOOLOW "Error: not a positive number."


typedef struct t_close {
    std::string	date;
    float		value;
}				t_close;

class BitcoinExchange {
private:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    std::multimap<std::string, float> container;
public:
    BitcoinExchange(std::ifstream &dataBase, const char &limiter);
    ~BitcoinExchange();

    void	ExchangeRate(const BitcoinExchange &input) const;
    bool	isValidFormat(std::string date, float value) const;
    bool	isValidDate(std::string line) const;
    void	printContent() const;
    void	findExchangeRate(std::string date, float value) const;
    void	findClosest(t_close &closest, const std::string &itDate, const float &itValue, const std::string &date) const;

    static time_t dateToTimestamp(const std::string& date);
    class CantOpenFile : public std::exception {
        public:
            const char* what() const throw() {
                return (CANTOPEN);
            }
    };
};
