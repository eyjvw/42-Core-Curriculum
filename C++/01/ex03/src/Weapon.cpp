/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 06:13:38 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/19 01:43:34 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(void) {
	this->type = "bare hands";
}

Weapon::Weapon(const char *type) {
	if (!type || type[0] == 0)
		this->type = "bare hands";
	else
		this->type = type;
}

std::string Weapon::getType()
{
	return (this->type);
}

void Weapon::setType(const char *type)
{
	if (!type || type[0] == 0)
		this->type = "bare hands";
	else
		this->type = type;
}

Weapon::~Weapon() {}