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

// Only digits, at least one, and the value must fit in an int
bool PmergeMe::isDigital(const char *av)
{
    if (av[0] == '\0')
        return (false);
    for (size_t i = 0; av[i]; i++) {
        if (!isdigit(static_cast<unsigned char>(av[i])))
            return (false);
    }

    errno = 0;
    long value = strtol(av, NULL, 10);

    return (errno != ERANGE && value <= INT_MAX);
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

// Inserts values[index] into chain (indices of values sorted by value), searching only chain[0, maxPosition)
template <typename T> void PmergeMe::binaryInsert(const T &values, T &chain, int index, size_t maxPosition)
{
    size_t left = 0;
    size_t right = maxPosition;

    while (left < right)
    {
        size_t mid = (left + right) / 2;
        
        if (values[index] < values[chain[mid]])
            right = mid;
        else
            left = mid + 1;
    }
    
    chain.insert(chain.begin() + left, index);
}

template <typename T> void PmergeMe::printStep(int step, T &container)
{
    typename T::const_iterator start = container.begin();
    typename T::const_iterator end = container.end();
    
    if (step == 1)
        std::cout << "Before: ";
    else
        std::cout << "After: ";

    while (start != end)
    {
        std::cout << *start;
        start++;

        if (start != end)
            std::cout << " ";
    }

    std::cout << std::endl;
}

// Ford-Johnson merge-insertion: fills order with the indices of values in sorted order
template <typename T> void PmergeMe::mergeInsert(const T &values, T &order)
{
    size_t half = values.size() / 2;

    order.clear();
    if (values.size() < 2)
    {
        if (values.size() == 1)
            order.push_back(0);
        return;
    }

    // 1. Compare each pair, the larger elements (winners) go to the next recursion level
    T winners;
    T winnerIdx;
    T loserIdx;

    for (size_t i = 0; i < half; i++)
    {
        int small = 2 * i;
        int large = 2 * i + 1;

        if (values[large] < values[small])
            std::swap(small, large);
        winners.push_back(values[large]);
        winnerIdx.push_back(large);
        loserIdx.push_back(small);
    }

    // 2. Recursively sort the winners
    T winnerOrder;

    this->mergeInsert(winners, winnerOrder);

    // 3. Main chain = sorted winners, pend = their losers in the same order (+ the odd element)
    T mainChain;
    T pend;

    for (size_t i = 0; i < half; i++)
    {
        mainChain.push_back(winnerIdx[winnerOrder[i]]);
        pend.push_back(loserIdx[winnerOrder[i]]);
    }
    if (values.size() % 2 != 0)
        pend.push_back(values.size() - 1);

    // 4. The first loser is smaller than the first winner: no comparison needed
    T chain(mainChain);

    chain.insert(chain.begin(), pend[0]);

    // 5. Insert the other losers by groups bounded by the Jacobsthal numbers, each group from its end,
    //    searching only the part of the chain before the loser's winner
    size_t prev = 1;

    for (size_t k = 3; prev < pend.size(); ++k)
    {
        size_t last = std::min(this->jacobSthal(k), pend.size());

        for (size_t j = last; j > prev; --j)
        {
            size_t maxPosition = chain.size();

            // Bound = position of the loser's winner: at least the j - 1 previous winners
            // and the prev losers of the previous groups are before it
            if (j - 1 < half)
                maxPosition = std::find(chain.begin() + (j - 1 + prev), chain.end(), mainChain[j - 1]) - chain.begin();
            this->binaryInsert(values, chain, pend[j - 1], maxPosition);
        }
        prev = last;
    }

    order = chain;
}

template <typename T> void PmergeMe::sort(T &container)
{
    T order;
    T sorted;

    this->mergeInsert(container, order);
    for (size_t i = 0; i < order.size(); i++)
        sorted.push_back(container[order[i]]);
    container = sorted;
}

bool PmergeMe::checkArgs(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return (false);
    }

    for (size_t i = 1; i < static_cast<size_t>(ac); i++)
    {
        if (!this->isDigital(av[i]))
        {
            std::cerr << "Error" << std::endl;
            return (false);
        }
    }

    return (true);
}

// Must be called once vec is sorted: duplicates are then next to each other
bool PmergeMe::hasNoDup(void)
{
    for (size_t i = 1; i < this->vec.size(); i++)
    {
        if (this->vec[i - 1] == this->vec[i])
        {
            std::cerr << "Error" << std::endl;
            return (false);
        }
    }
    
    return (true);
}

void PmergeMe::initVector(int ac, char **av)
{
    for (size_t i = 1; i < static_cast<size_t>(ac); i++)
        this->vec.push_back(atoi(av[i]));
}

bool PmergeMe::start(void)
{
    this->deq.assign(this->vec.begin(), this->vec.end());
    
    double vecStartTime;
    double vecEndTime;
    double deqStartTime;
    double deqEndTime;

    vecStartTime = this->getTime();
    this->sort(this->vec);
    vecEndTime = this->getTime();

    if (!this->hasNoDup())
        return (false);
    this->printStep(1, this->deq);

    deqStartTime = this->getTime();
    this->sort(this->deq);
    deqEndTime = this->getTime();

    this->printStep(2, this->vec);

    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Time to process a range of " << this->vec.size()  << " elements with std::vector : "  << (vecEndTime - vecStartTime) << " us" << std::endl;
    std::cout << "Time to process a range of " << this->deq.size()  << " elements with std::deque : "  << (deqEndTime - deqStartTime) << " us" << std::endl;

    return (true);
}
