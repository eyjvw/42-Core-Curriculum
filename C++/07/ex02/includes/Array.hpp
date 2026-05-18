/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 07:42:39 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 08:19:52 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

template <class T>
class Array
{
    private:
        T				*array;
        unsigned int	_size;
    public:
        Array(void);
        Array(const unsigned int size);
        Array(const Array &other);
        Array &operator=(const Array &other);
        ~Array(void);

        class InvalidIndex : public std::exception
        {
            public:
                const char* what() const throw()
                {
                    return ("Index out of bounds");
                }
        };
        
        unsigned int size(void) const;
        const T &operator[](const int pos) const;
        T &operator[](const int pos);
};

#include "Array.tpp"