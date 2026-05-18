/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 05:51:57 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/30 05:54:01 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

template<typename T>
MutantStack<T>::MutantStack(const MutantStack &src)
{
    this->c = src.c;
}

template<typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack &src)
{
    this->c = src.c;

    return (*this);
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
    return(this->c.begin());
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
    return(this->c.end());
}

template<typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin()
{
    return(this->c.rbegin());
}

template<typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend()
{
    return(this->c.rend());
}

template<typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::cbegin()
{
    return(this->c.begin());
}

template<typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::cend()
{
    return(this->c.end());
}

template<typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::crbegin()
{
    return(this->c.rbegin());}

template<typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::crend() {
    return(this->c.rend());
}