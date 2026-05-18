/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 01:57:54 by sbonneau          #+#    #+#             */
/*   Updated: 2026/02/01 03:14:27 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;

    return (*this);
}

PmergeMe::~PmergeMe(void) {}

double PmergeMe::getTime(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

bool PmergeMe::isDigital(const char *av)
{
    for (size_t i = 0; i < strlen(av); i++) {
        if (!isdigit(av[i]))
		    return (false);
	}

    return (true);
}

size_t PmergeMe::jacobSthal(size_t n)
{
    if (n == 0)
        return (0);
    if (n == 1)
        return (1);

    size_t a = 0;
    size_t b = 1;
    size_t c;

    for (size_t i = 2; i <= n; ++i)
    {
        c = b + 2 * a;
        a = b;
        b = c;
    }
    
    return (b);
}

template <typename T> void PmergeMe::binaryInsert(T &container, int value, size_t maxPosition)
{
    size_t left = 0;
    size_t right = maxPosition;

    while (left < right)
    {
        size_t mid = (left + right) / 2;
        
        if (value < container[mid])
            right = mid;
        else
            left = mid + 1;
    }
    
    container.insert(container.begin() + left, value);
}

template <typename T> void PmergeMe::printStep(int step, T &container)
{
    typename T::const_iterator start = container.begin();
    typename T::const_iterator end = container.end();
    
    if (step == 1)
        std::cout << "Before : ";
    else
        std::cout << "After : ";

    while (start != end)
    {
        std::cout << *start;
        start++;

        if (start != end)
            std::cout << " ";
    }

    std::cout << std::endl;
}

template <typename T> void PmergeMe::sort(T &container)
{
    if (container.size() <= 1)
        return;

    T small;
    T large;

    for (size_t i = 0; i + 1 < container.size(); i += 2)
    {
        if (container[i] < container[i + 1])
        {
            small.push_back(container[i]);
            large.push_back(container[i + 1]);
        }
        else
        {
            small.push_back(container[i + 1]);
            large.push_back(container[i]);
        }
    }

    bool hasOdd = (container.size() % 2 != 0);
    int odd;
    if (hasOdd)
        odd = container.back();

    PmergeMe::sort(large);
    
    T result = large;
    
    std::vector<size_t> order;
    size_t k = 1;

    while (this->jacobSthal(k) < small.size())
    {
        order.push_back(this->jacobSthal(k));
        ++k;
    }
    
    if (small.size() > 0)
        order.push_back(small.size());
    
    size_t prev = 0;
    size_t inserted = 0;
    
    for (size_t i = 0; i < order.size(); ++i)
    {
        for (size_t j = order[i]; j-- > prev;)
        {
            binaryInsert(result, small[j], large.size() + inserted);
            ++inserted;
        }
        prev = order[i];
    }

    if (hasOdd)
        binaryInsert(result, odd, result.size());

    container = result;
}

bool PmergeMe::checkArgs(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Wrong number of args" << std::endl;
        return (false);
    }

    for (size_t i = 1; i < static_cast<size_t>(ac); i++)
    {
		if (!this->isDigital(av[i]))
        {
			std::cerr << "Only positive number" << std::endl;
			return (false);
		}
	}

    return (true);
}

bool PmergeMe::hasNoDup(int ac, char **av)
{
    for (size_t i = 1; i < static_cast<size_t>(ac); i++)\
    {
		for (size_t j = i + 1; j < static_cast<size_t>(ac); j++)\
        {
			if (atoi(av[i]) == atoi(av[j]))
            {
				std::cerr << "Only different number" << std::endl;
				return (false);
			}
		}
	}
    
	return (true);
}

void PmergeMe::initVector(int ac, char **av)
{
    for (size_t i = 1; i < static_cast<size_t>(ac); i++)
        this->vec.push_back(atoi(av[i]));
}

void PmergeMe::start(void)
{
    this->printStep(1, this->vec);

    std::deque<int> deq(vec.begin(), vec.end());
    
    double vecStartTime;
    double vecEndTime;
    double deqStartTime;
    double deqEndTime;

    vecStartTime = this->getTime();
    this->sort(vec);
    vecEndTime = this->getTime();

    deqStartTime = this->getTime();
    PmergeMe::sort(deq);
    deqEndTime = this->getTime();

    this->printStep(2, vec);

    std::cout << "Time to process a range of " << vec.size()  << " elements with std::vector : "  << (vecEndTime - vecStartTime) << " us" << std::endl;
    std::cout << "Time to process a range of " << vec.size()  << " elements with std::deque : "  << (deqEndTime - deqStartTime) << " us" << std::endl;
}