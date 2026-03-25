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
    
    std::ifstream infile(av[1]);
    std::ofstream outfile(outfile_name.c_str());
    std::string current_line;
    size_t pos;
    
    if (s1.empty())
    {
        std::cerr << "Error : s1 is empty" << std::endl;
        return (0);
    }
    if (s2.empty())
    {
        std::cerr << "Error : s2 is empty" << std::endl;
        return (0);
    }
    if (!infile.is_open())
    {
        std::cerr << "Error : infile is not open" << std::endl;
        return (0);
    }
    if (!outfile.is_open())
    {
        std::cerr << "Error : outfile is not open " << std::endl;
        return (0);
    }

    while (std::getline(infile, current_line))
    {
        while (1)
        {
            pos = current_line.find(s1);
            if (pos == std::string::npos)
                break ;
            current_line = current_line.substr(0, pos) + s2 + current_line.substr(pos + s1.length(), current_line.length());
        }
        outfile << current_line << std::endl;
    }

    infile.close();
    outfile.close();

    return (0);
}