/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 01:55:24 by sbonneau          #+#    #+#             */
/*   Updated: 2026/02/01 03:11:56 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cctype>
#include <sys/time.h>

class PmergeMe
{
    private:
        std::vector<int> vec;
        std::deque<int> deq;
        
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        double getTime(void);
        bool isDigital(const char *av);
        size_t jacobSthal(size_t n);
        template <typename T> void binaryInsert(const T &values, T &chain, int index, size_t maxPosition);
        template <typename T> void printStep(int step, T &container);
        template <typename T> void mergeInsert(const T &values, T &order);
        template <typename T> void sort(T &container);
    public:
        PmergeMe(void);
        ~PmergeMe(void);

        bool checkArgs(int ac, char **av);
        bool hasNoDup(void);
        void initVector(int ac, char **av); 
        bool start(void);
};
