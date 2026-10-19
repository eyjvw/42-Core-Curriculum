/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:48:53 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 21:51:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/easyfind.hpp"
#include <list>
#include <deque>
#include <iterator>

template <typename T> void test(T &container, int value)
{
    typename T::iterator it = easyfind(container, value);

    std::cout << "Value : " << value;
    if (it == container.end())
        std::cout << " not found in container" << std::endl;
    else
        std::cout << " found in container at position " << std::distance(container.begin(), it) << std::endl;
}

int main(void)
{
    std::vector<int> vec;
    std::list<int> lst;
    std::deque<int> deq;
    
    for (int i = 0;i <= 100;i++)
    {
        vec.push_back(i);
        lst.push_back(i * 2);
        deq.push_front(i);
    }

    test(vec, 101);
    test(vec, 100);
    test(lst, 42);
    test(lst, 43);
    test(deq, 0);
    test(deq, -1);

    const std::vector<int> constVec(vec);
    std::vector<int>::const_iterator it = easyfind(constVec, 50);

    std::cout << "Value : 50" << (it != constVec.end() ? " found" : " not found") << " in const container" << std::endl;

    return (0);
}
