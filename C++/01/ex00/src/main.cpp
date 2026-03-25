/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:04:49 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/15 13:15:50 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *zombie = newZombie("Sbonneauuuuuuu");
	
	zombie->announce();
	randomChump("Hoel");
	zombie->announce();
	randomChump("Alexandru");
	zombie->announce();
	delete (zombie);
	return (0);
}