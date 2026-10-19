/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ft.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:29:27 by hkeromne          #+#    #+#             */
/*   Updated: 2026/02/16 23:40:40 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Ft.hpp"


bool Ft::endsWithLF(const std::string& s)
{
    return (!s.empty() && s[s.size() - 1] == '\n');
}

std::string Ft::toCRLF(std::string const &line)
{
	std::string	res(line);

	if (!res.empty() && res[res.size() - 1] == '\n')
		res.erase(res.size() - 1);
	if (!res.empty() && res[res.size() - 1] == '\r')
		res.erase(res.size() - 1);
	return (res + "\r\n");
}

std::string Ft::toLower(std::string const &s)
{
	std::string	res(s);

	for (size_t i = 0; i < res.length(); i++)
	{
		if (res[i] >= 'A' && res[i] <= '^')
			res[i] = res[i] + ('a' - 'A');
	}
	return (res);
}

std::vector<std::string>	Ft::split(std::string const &s, char sep)
{
	std::vector<std::string>	res;
	std::string					token;
	std::stringstream			stream(s);

	while (std::getline(stream, token, sep))
		res.push_back(token);
	return (res);
}

std::string Ft::extractLine(std::string &buffer)
{
	std::size_t	pos;
	std::string line;

	if (buffer.empty())
		return ("");
	pos = buffer.find('\n');
	pos = (pos == std::string::npos) ? buffer.length() : pos + 1;
	line = buffer.substr(0, pos);
	buffer.erase(0, pos);

	return (line);
}

std::string	Ft::getFdContent(const int fd)
{
	std::string	file;
	int			bytes;

	file.resize(BUFFER_SIZE);
	bytes = recv(fd, &file[0], BUFFER_SIZE, 0);
	if (bytes <= 0)
		return ("");
	file.resize(bytes);
	return (file);
}

static bool isLetter(char c)	{ return std::isalpha(static_cast<unsigned char>(c)) != 0; };
static bool isDigit(char c)		{ return std::isdigit(static_cast<unsigned char>(c)) != 0; };
static bool isSpecial(char c)	{ return (c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7D); };

bool Ft::isValidNickname(const std::string &nick)
{
    if (nick.empty() || nick.length() > 9)
        return (false);

    char first = nick[0];
    if (!(isLetter(first) || isSpecial(first)))
        return (false);

    for (std::string::size_type i = 1; i < nick.length(); ++i)
    {
        char c = nick[i];
        if (!(isLetter(c) || isDigit(c) || isSpecial(c) || c == '-'))
            return (false);
    }

    return (true);
}


bool Ft::isValidChannelName(std::string const &name)
{
    if (name.empty() || name.length() > 200 || name[0] != '#' || name.size() < 2)
        return (false);
    
    for (size_t i = 1; i < name.length(); ++i)
	{
        unsigned char c = static_cast<unsigned char>(name[i]);
        
        if (c == ' ' || c == ','
		|| c == '\007' || c == '\0' || c <= 0x1F)
			return (false);
    }
    return (true);
}

bool Ft::isInt(const std::string &sNum)
{
    size_t start = 0;

    if (sNum.empty())
        return false;
    
    if ((sNum[0] == '+' || sNum[0] == '-'))
	{
		if (sNum.length() == 1)
			return (false);
		start = 1;
	}
    
    for (size_t i = start; i < sNum.length(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(sNum[i])))
            return (false);
    }
    
    return (true);
}

int			Ft::strToInt(std::string const &sNum)
{
	int					result;
	std::stringstream	stream;

	stream << sNum;
	stream >> result;

	if (!stream.eof() || stream.fail())
		return (INT_MIN);
	return (result);
}

std::string	Ft::intToStr(const int &num)
{
	std::stringstream	s;
	std::string			sNum;

	s << num;
	s >> sNum;

	return (sNum);
}


std::string Ft::getTime(void)
{
	std::time_t now = std::time(NULL);
	std::tm* t = std::localtime(&now);

	char buffer[100];
	std::strftime(buffer, sizeof(buffer),
			"%a %b %d %Y at %H:%M:%S %Z", t);

	return std::string(buffer);
}
