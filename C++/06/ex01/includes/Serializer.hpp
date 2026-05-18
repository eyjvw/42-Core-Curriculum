/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 02:32:37 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/25 03:31:03 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdint.h>

typedef struct sData
{
    int x;
} Data;

class Serializer
{
    public:
        Serializer(void);
        Serializer(const Serializer &other);
        Serializer &operator=(const Serializer &other);
        ~Serializer(void);

        static uintptr_t serialize(Data *ptr);
        static Data *deserialize(uintptr_t raw);
};