/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:50:42 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/24 00:24:09 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <deque>
#include <stdexcept>
#include <limits>
#include <cerrno>
#include "utils.hpp"

enum type
{
	A = 0,
	B = 1
};

struct Pair
{
	size_t index;
	type pair_type;
	std::vector<int> pair;
};

class Pmerge
{
private:
	int jcb_start;
	std::vector<int> _numbers;
	std::vector<Pair> _main;
	std::vector<int> _rest;
	std::vector<Pair> _pend;

	Pmerge(/* args */);

public:
	// ========================================================================
	// CONSTRUCTORS AND DESTRUCTOR
	// ========================================================================
	Pmerge(int ac, char **av);

	Pmerge(const Pmerge &src);

	Pmerge &operator=(const Pmerge &rhs);

	~Pmerge();

	// ========================================================================
	// PARSING AND VALIDATION FUNCTIONS
	// ========================================================================

	bool isDigit(const std::string &str) const;

	bool isValidInt(const std::string &str) const;

	bool has_duplicates(const std::vector<int> &vec);

	bool is_sort(const std::vector<int> &vec);

	// ========================================================================
	// SORTING FUNCTIONS (FORD-JOHNSON ALGORITHM)
	// ========================================================================

	void sort();

	size_t createPairs();

	void makePairs(std::vector<Pair> &pairs, size_t pairSize);

	void recursivePairs(std::vector<Pair> &pairs, size_t pairSize);

	void insert_pair(std::vector<Pair> &main, const Pair &element, int search_limit);

	static bool compare_pairs(const Pair &a, const Pair &b);

	size_t find_partner_position(const Pair &pend_element);

	static int jacobstahl_numbers(int n);

	// ========================================================================
	// DISPLAY AND DEBUG FUNCTIONS
	// ========================================================================

	void displayNumbers() const;
	void displayRest() const;
	void displayMain() const;
	void displayPend() const;
	void displayPair(const std::vector<Pair> &pairs) const;

	std::vector<int> getNumbers() const;
};

#endif