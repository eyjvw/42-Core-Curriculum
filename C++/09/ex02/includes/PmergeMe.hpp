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
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <sys/time.h>
#include <string.h>

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
        template <typename T> void binaryInsert(T &container, int value, size_t maxPosition);
        template <typename T> void printStep(int step, T &container);
        template <typename T> void sort(T &container);
    public:
        PmergeMe(void);
        ~PmergeMe(void);

        bool checkArgs(int ac, char **av);
        bool hasNoDup(int ac, char **av);
        void initVector(int ac, char **av); 
        void start(void);
};