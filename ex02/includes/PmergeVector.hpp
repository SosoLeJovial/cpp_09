#ifndef PMERGEVECTOR_HPP
#define PMERGEVECTOR_HPP

#include <string>
#include <sys/time.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <stdexcept>
#include <limits>
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

class PmergeVector
{
private:
	struct timeval start, end;
	int jcb_start;
	std::vector<int> _numbers;
	std::vector<Pair> _main;
	std::vector<int> _rest;
	std::vector<Pair> _pend;

	PmergeVector(/* args */);

public:
	// ========================================================================
	// CONSTRUCTORS AND DESTRUCTOR
	// ========================================================================
	PmergeVector(int ac, char **av);
	PmergeVector(const PmergeVector &src);
	PmergeVector &operator=(const PmergeVector &rhs);
	~PmergeVector();

	// ========================================================================
	// PARSING AND VALIDATION FUNCTIONS
	// ========================================================================
	bool isDigit(const std::string &str) const;
	bool isValidInt(const std::string &str) const;
	bool has_duplicates(const std::vector<int> &vec);
	bool is_sort(std::vector<int> &vec);

	// ========================================================================
	// SORTING FUNCTIONS (FORD-JOHNSON ALGORITHM)
	// ========================================================================
	void sort();
	size_t createPairs();
	void makePairs(std::vector<Pair> &pairs, size_t pairSize);
	void recursivePairs(std::vector<Pair> &pairs, size_t pairSize);
	void insert_pair(std::vector<Pair> &main, const Pair &element, int search_limit);
	size_t find_partner_position(const Pair &pend_element);
	static bool compare_pairs(const Pair &a, const Pair &b);
	int jacobstahl_numbers(int n);

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