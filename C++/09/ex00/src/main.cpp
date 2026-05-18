/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 20:16:50 by sbonneau          #+#    #+#             */
/*   Updated: 2026/02/02 01:50:37 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int	main(int ac, char **av) {
	if (ac != 2)
    {
		std::cout << CANTOPEN << std::endl;
		return (1);
	}
    
	try {
		std::ifstream data(DBSOURCE);
		BitcoinExchange btc(data, ',');
        
		std::ifstream src(av[1]);
		BitcoinExchange input(src, '|');
        
		btc.ExchangeRate(input);
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
    
	return (0);
}
