/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:58:21 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 08:03:14 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include <ctime>

#define RobotomyName "RobotomyRequestForm"
#define RobotomySignGrade 72
#define RobotomyExecGrade 45

class RobotomyRequestForm : public AForm
{
    public:
        RobotomyRequestForm(void);
        RobotomyRequestForm(const std::string target);
        RobotomyRequestForm(const RobotomyRequestForm &other);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
        ~RobotomyRequestForm(void);
        
        void executeContract(void) const;
        void executeForm(void) const;
};

std::ostream &operator<<(std::ostream &os, const RobotomyRequestForm &form);