/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 08:04:39 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 08:21:36 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class T>
Array<T>::Array(void): _size(0)
{
    this->array = new T[0];
}

template <class T>
Array<T>::Array(const unsigned int n): _size(n)
{
    this->array = new T[n];
}

template <class T>
Array<T>::Array(const Array &other): _size(other._size)
{
    this->array = new T[this->_size];

    for (unsigned int i = 0; i < this->_size; i++)
        this->array[i] = other.array[i];
}

template <class T>
Array<T> &Array<T>::operator=(const Array<T> &other)
{
    if (this != &other)
    {
        delete[] this->array;
        this->_size = other._size;
        this->array = new T[this->_size];

        for (unsigned int i = 0; i < this->_size; i++)
            this->array[i] = other.array[i];
    }
    
    return (*this);
}

template <class T>
Array<T>::~Array(void)
{
    delete[] this->array;
}

template <class T>
unsigned int Array<T>::size(void) const
{
    return (this->_size);
}

template <class T>
const T &Array<T>::operator[](const int pos) const
{
    if (pos < 0 || static_cast<unsigned int>(pos) >= this->_size)
        throw(Array::InvalidIndex());
    return (this->array[pos]);
}

template <class T>
T &Array<T>::operator[](const int pos)
{
    if (pos < 0 || static_cast<unsigned int>(pos) >= this->_size)
        throw(Array::InvalidIndex());
    return (this->array[pos]);
}