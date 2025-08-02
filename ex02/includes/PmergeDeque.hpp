/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeDeque.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:50:42 by tsofien-          #+#    #+#             */
/*   Updated: 2025/08/02 17:00:21 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEDEQUE_HPP
#define PMERGEDEQUE_HPP

#include "PmergeVector.hpp"
#include <deque>

struct PairDeque
{
	size_t index;
	type pair_type;
	std::deque<int> pairDeque;
};

class PmergeDeque
{
private:
	struct timeval start, end;
	int jcb_start;
	std::deque<int> _numbers;
	std::deque<PairDeque> _main;
	std::deque<int> _rest;
	std::deque<PairDeque> _pend;

	PmergeDeque(/* args */);

public:
	// ========================================================================
	// CONSTRUCTORS AND DESTRUCTOR
	// ========================================================================
	PmergeDeque(int ac, char **av);
	PmergeDeque(const PmergeDeque &src);
	PmergeDeque &operator=(const PmergeDeque &rhs);
	~PmergeDeque();

	// ========================================================================
	// PARSING AND VALIDATION FUNCTIONS
	// ========================================================================
	bool isDigit(const std::string &str) const;
	bool isValidInt(const std::string &str) const;
	bool has_duplicates(const std::deque<int> &vec);
	bool is_sort(std::deque<int> &vec);

	// ========================================================================
	// SORTING FUNCTIONS (FORD-JOHNSON ALGORITHM)
	// ========================================================================
	void sort();
	size_t createPairDeques();
	void makePairDeques(std::deque<PairDeque> &PairDeques, size_t PairDequeSize);
	void recursivePairDeques(std::deque<PairDeque> &PairDeques, size_t PairDequeSize);
	void insert_PairDeque(std::deque<PairDeque> &main, const PairDeque &element, int search_limit);
	size_t find_partner_position(const PairDeque &pend_element);
	static bool compare_PairDeques(const PairDeque &a, const PairDeque &b);
	int jacobstahl_numbers(int n);

	// ========================================================================
	// DISPLAY AND DEBUG FUNCTIONS
	// ========================================================================
	void displayNumbers() const;
	void displayRest() const;
	void displayMain() const;
	void displayPend() const;
	void displayPairDeque(const std::deque<PairDeque> &PairDeques) const;

	std::deque<int> getNumbers() const;
};

#endif