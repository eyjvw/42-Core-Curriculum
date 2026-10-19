/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 05:54:04 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/30 05:56:16 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/MutantStack.hpp"
#include <list>

int main(void)
{
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);

    std::cout << "--- std::list comparison" << std::endl;
    std::list<int> lst;

    lst.push_back(5);
    lst.push_back(17);
    std::cout << lst.back() << std::endl;
    lst.pop_back();
    std::cout << lst.size() << std::endl;
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    for (std::list<int>::iterator lit = lst.begin(); lit != lst.end(); ++lit)
        std::cout << *lit << std::endl;

    std::cout << "--- copy, const and reverse iterators" << std::endl;
    MutantStack<int> copy(mstack);
    const MutantStack<int> &constRef = copy;

    copy.push(42);
    for (MutantStack<int>::const_iterator cit = constRef.begin(); cit != constRef.end(); ++cit)
        std::cout << *cit << " ";
    std::cout << std::endl;
    for (MutantStack<int>::const_reverse_iterator rit = constRef.rbegin(); rit != constRef.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << std::endl;
    std::cout << "original size " << mstack.size() << ", copy size " << copy.size() << ", std::stack copy top " << s.top() << std::endl;

    return (0);
}
