/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 01:45:53 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:18:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <fstream>

int main(int ac, char **av)
{
    if (ac != 4)
    {
        std::cerr << "Correct usage : ./Sed filename s1 s2" << std::endl;
        return (1);
    }
    
    std::string s1(av[2]);
    std::string s2(av[3]);
    std::string outfile_name(av[1]);

    outfile_name += ".replace";
    
    std::string content;
    std::string result;
    std::string current_line;
    size_t start;
    size_t pos;
    
    if (s1.empty())
    {
        std::cerr << "Error : s1 is empty" << std::endl;
        return (1);
    }

    std::ifstream infile(av[1]);
    if (!infile.is_open())
    {
        std::cerr << "Error : infile is not open" << std::endl;
        return (1);
    }
    while (std::getline(infile, current_line))
    {
        content += current_line;
        if (!infile.eof())
            content += '\n';
    }
    if (infile.bad())
    {
        std::cerr << "Error : infile can not be read" << std::endl;
        return (1);
    }
    infile.close();

    start = 0;
    pos = content.find(s1);
    while (pos != std::string::npos)
    {
        result += content.substr(start, pos - start) + s2;
        start = pos + s1.length();
        pos = content.find(s1, start);
    }
    result += content.substr(start);

    std::ofstream outfile(outfile_name.c_str());
    if (!outfile.is_open())
    {
        std::cerr << "Error : outfile is not open " << std::endl;
        return (1);
    }
    outfile << result;
    outfile.close();
    if (outfile.fail())
    {
        std::cerr << "Error : outfile can not be written" << std::endl;
        return (1);
    }

    return (0);
}