/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:50:42 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/16 14:49:42 by tsofien-         ###   ########.fr       */
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
	std::vector<int> _numbers;
	std::vector<int> _main;
	std::vector<int> _rest;
	std::vector<int> _pend;

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

	// ========================================================================
	// SORTING FUNCTIONS (FORD-JOHNSON ALGORITHM)
	// ========================================================================

	void sort();

	void createPairs();

	void makePairs(std::vector<Pair> &pairs, size_t pairSize);

	void recursivePairs(std::vector<Pair> &pairs, size_t pairSize);

	// ========================================================================
	// DISPLAY AND DEBUG FUNCTIONS
	// ========================================================================

	void displayNumbers() const;

	void displayPair(const std::vector<Pair> &pairs) const;

};

#endif