/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:35:05 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/15 13:16:12 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	int N = 2;
	std::string name = "Hoel";
	Zombie *horde = zombieHorde(N, name);

	for (int i = 0;i < N;i++)
		horde[i].announce();
	delete [](horde);
	return (0);
}