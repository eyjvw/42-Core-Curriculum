/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:33:15 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/22 20:45:48 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AForm.hpp"

class Intern
{
    public:
        Intern(void);
        Intern(const Intern &other);
        Intern &operator=(const Intern &other);
        ~Intern(void);

        class InvalidForm : public std::exception
        {
            public:
                const char *what() const throw()
                {
                    return ("This form doesn't exist");
                }
        };
        
        AForm* makeForm(const std::string formName, const std::string targetName) const;
};