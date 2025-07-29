/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:50:42 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/29 20:17:54 by tsofien-         ###   ########.fr       */
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

template <typename Container>
class Pmerge
{
private:
	int jcb_start;
	Container _numbers;
	std::vector<Pair> _main;
	Container _rest;
	std::vector<Pair> _pend;

	Pmerge(/* args */);

public:
	// ========================================================================
	// CONSTRUCTORS AND DESTRUCTOR
	// ========================================================================
	Pmerge(int ac, char **av)
	{
		if (ac < 2)
		{
			std::cerr << RED << "Usage: " << av[0] << " <numbers>" << RESET << std::endl;
			throw std::invalid_argument("Invalid number of arguments");
		}
		std::vector<int> all_numbers;
		for (int i = 1; i < ac; i++)
		{
			if (!isValidInt(av[i]))
			{
				std::cerr << RED << "Error: Invalid input. Only integers are allowed." << RESET << std::endl;
				throw std::invalid_argument("Invalid input");
			}
			all_numbers.push_back(std::atoi(av[i]));
		}
		for (size_t i = 0; i < all_numbers.size(); i++)
			_numbers.push_back(all_numbers[i]);
		std::cout << GREEN << "Before: " << RESET;
		displayNumbers();
	}

	Pmerge(const Pmerge &src)
	{
		if (this != &src)
		{
			jcb_start = src.jcb_start;
			_numbers = src._numbers;
			_main = src._main;
			_rest = src._rest;
			_pend = src._pend;
		}
	}

	Pmerge &operator=(const Pmerge &rhs)
	{
		if (this != &rhs)
		{
			jcb_start = rhs.jcb_start;
			_numbers = rhs._numbers;
			_main = rhs._main;
			_rest = rhs._rest;
			_pend = rhs._pend;
		}
		return *this;
	}

	~Pmerge() {};
	// ========================================================================
	// PARSING AND VALIDATION FUNCTIONS
	// ========================================================================

	bool isDigit(const std::string &str) const
	{
		if (str.empty())
			return false;
		size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		for (size_t i = start; i < str.length(); i++)
		{
			if (!std::isdigit(str[i]))
				return false;
		}
		return true;
	}

	bool isValidInt(const std::string &str) const
	{
		if (str.empty() || str[0] == '-' || str[0] == '+')
			return false;

		size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		for (size_t i = start; i < str.length(); i++)
		{
			if (!std::isdigit(str[i]))
				return false;
		}

		char *endptr;
		errno = 0;
		long val = std::strtol(str.c_str(), &endptr, 10);

		return (errno != ERANGE && *endptr == '\0' &&
				val >= std::numeric_limits<int>::min() &&
				val <= std::numeric_limits<int>::max());
	}

	bool has_duplicates(const Container &vec)
	{
		Container seen;
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (std::find(seen.begin(), seen.end(), vec[i]) != seen.end())
				return true;
			seen.push_back(vec[i]);
		}
		return false;
	}

	bool is_sort(Container &vec)
	{

		for (typename Container::const_iterator it = vec.begin(); it != vec.end(); ++it)
		{
			if (it + 1 != vec.end() && *it > *(it + 1))
				return false;
		}
		return true;
	}

	// ========================================================================
	// SORTING FUNCTIONS (FORD-JOHNSON ALGORITHM)
	// ========================================================================

	void sort()
	{
		std::vector<Pair> pairs;
		int stragglers = -1;

		if (has_duplicates(_numbers))
		{
			std::cerr << RED << "Error: Duplicate found." << RESET << std::endl;
			throw std::invalid_argument("Invalid number: duplicate");
		}

		if (is_sort(_numbers))
		{
			std::cout << RED << "Error: Numbers are already sorted." << RESET << std::endl;
			throw std::invalid_argument("Invalid number: already sorted");
		}

		if (_numbers.size() % 2 != 0)
		{
			stragglers = _numbers.back();
			_numbers.pop_back();
		}

		
		
		size_t pairSize = createPairs();
		makePairs(pairs, pairSize);
		
#ifdef DEBUG
		std::cout << YELLOW << "=== STEPS 1: MAKING PAIRS AND HANDLE STRAGGLER ===" << RESET << std::endl;
		std::cout << YELLOW << "=== STEPS 2: SORT PAIRS ===" << RESET << std::endl;
		displayPair(pairs);
		if (stragglers != -1)
			std::cout << "Straggler store: " << stragglers << std::endl;
		else
			std::cout << "Straggler store: " << "none" << std::endl;
		std::cout << YELLOW << "=== STEP 3: RECURSIVE PAIRS ===" << RESET << std::endl;
		// std::cout << YELLOW << "=== STEP 3: RECURSIVE PAIRS ===" << RESET << std::endl;
		// std::cout << YELLOW << "=== STEP 3: RECURSIVE PAIRS ===" << RESET << std::endl;
#endif

		recursivePairs(pairs, pairSize);
		if (stragglers != -1)
		{
			Container stragglers_vector;
			stragglers_vector.push_back(stragglers);
			typename Container::iterator it = std::lower_bound(_numbers.begin(), _numbers.end(), stragglers);
			_numbers.insert(it, stragglers_vector.begin(), stragglers_vector.end());
		}
		std::cout << GREEN << "After: " << RESET;
		displayNumbers();
	}

	size_t createPairs()
	{
		size_t size = _numbers.size();
		size_t pairSize = 2;
		size_t levels = 0;

		while (pairSize <= size)
		{
			for (size_t j = (pairSize / 2) - 1; j + (pairSize / 2) < size; j += pairSize)
			{
				if (j < size && j + (pairSize / 2) < size && _numbers[j] > _numbers[j + (pairSize / 2)])
				for (size_t k = j - (pairSize / 2) + 1; k <= j; k++)
				std::swap(_numbers[k], _numbers[k + (pairSize / 2)]);
			}
			pairSize *= 2;
			levels++;
		}
		if (size == 2)
			return 2;
		return pairSize / 2;
	}



	void makePairs(std::vector<Pair> &pairs, size_t pairSize)
	{
		pairs.clear();
		size_t size = _numbers.size();
		if (pairSize < 1)
			return;

		for (size_t i = 0; i < size; i += pairSize)
		{
			if (i + pairSize > size)
				break;

			size_t pair_number = i / pairSize;
			type pair_side = pair_number % 2 ? B : A;
			size_t index = pair_number / 2 + 1;

			std::vector<int> numbers(_numbers.begin() + i, _numbers.begin() + i + pairSize);
			Pair new_pair = {index, pair_side, numbers};
			pairs.push_back(new_pair);
		}
	}

	void recursivePairs(std::vector<Pair> &pairs, size_t pairSize)
	{
		if (pairSize < 1)
			return;

		_main.clear();
		_pend.clear();
		_rest.clear();

		size_t restIndex = _numbers.size() % pairSize;
		size_t sizeNumbers = _numbers.size();
		for (int i = sizeNumbers - 1; i >= (int)(sizeNumbers - restIndex); i--)
		{
			_rest.push_back(_numbers[i]);
			_numbers.pop_back();
		}

		for (std::vector<Pair>::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
		{
			if (it->pair_type == A)
			{
				if (it->index == 1)
					_main.push_back(*it);
				else
					_pend.push_back(*it);
			}
			else
				_main.push_back(*it);
		}

		#ifdef DEBUG
		std::cout << YELLOW << "=== STEP 4: SORT IN PEND AND MAIN ===" << RESET << std::endl;
		displayNumbers();
		displayMain();
		displayPend();
		#endif

		size_t previousLimit = 1;
		int jcb_start = 3;
		while (previousLimit < _pend.size())
		{
			size_t currentLimit = jacobstahl_numbers(jcb_start);
			size_t end = (currentLimit < _pend.size()) ? currentLimit : _pend.size();
			for (size_t i = end; i > previousLimit; i--)
			{
				size_t partner_pos = find_partner_position(_pend[i - 1]);
				insert_pair(_main, _pend[i - 1], partner_pos);
			}

			_pend.erase(_pend.begin() + previousLimit, _pend.begin() + end);
			previousLimit = currentLimit;
			jcb_start++;
		}

		if (!_pend.empty())
		{
			for (std::vector<Pair>::const_iterator it = _pend.begin(); it != _pend.end(); ++it)
			{
				size_t partner_pos = find_partner_position(*it);
				insert_pair(_main, *it, partner_pos);
			}
		}
		
		_pend.clear();
		_numbers.clear();
		#ifdef DEBUG
			std::cout << YELLOW << "=== STEP 5: SORT IN MAIN ===" << RESET << std::endl;
			displayMain();
			displayPend();
			displayRest();
		#endif

		for (std::vector<Pair>::const_iterator it = _main.begin(); it != _main.end(); ++it)
			for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
				_numbers.push_back(*vec_it);

		for (typename Container::reverse_iterator it = _rest.rbegin(); it != _rest.rend(); ++it)
			_numbers.push_back(*it);
		

		if (pairSize > 1)
			pairSize /= 2;
		else
			pairSize = 0;

		makePairs(pairs, pairSize);
		recursivePairs(pairs, pairSize);
	}

	void insert_pair(std::vector<Pair> &main, const Pair &element, int search_limit)
	{
		std::vector<Pair>::iterator it = std::lower_bound(main.begin(), main.begin() + search_limit,
														  element, compare_pairs);
		main.insert(it, element);
	}

	size_t find_partner_position(const Pair &pend_element)
	{
		for (size_t i = 0; i < _main.size(); i++)
		{
			if (_main[i].index == pend_element.index && _main[i].pair_type == B)
				return i + 1;
		}
		return _main.size();
	}

	static bool compare_pairs(const Pair &a, const Pair &b)
	{
		return a.pair.back() < b.pair.back();
	}

	int jacobstahl_numbers(int n)
	{
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;

		int prev2 = 0, prev1 = 1;
		for (int i = 2; i <= n; i++)
		{
			int current = prev1 + 2 * prev2;
			prev2 = prev1;
			prev1 = current;
		}
		return prev1;
	}

	// ========================================================================
	// DISPLAY AND DEBUG FUNCTIONS
	// ========================================================================

	void displayNumbers() const
	{
		std::cout << YELLOW << "Display numbers: ";
		for (typename Container::const_iterator it = _numbers.begin(); it != _numbers.end(); ++it)
		{
			std::cout << BLUE << *it << " ";
		}
		std::cout << RESET << std::endl;
	}

	void displayRest() const
	{
		std::cout << CYAN << "Rest numbers: ";
		if (_rest.empty())
		{
			std::cout << CYAN << "None" << RESET << std::endl;
			return;
		}
		for (typename Container::const_iterator it = _rest.begin(); it != _rest.end(); ++it)
			std::cout << RESET << *it << " ";
		std::cout << RESET << std::endl;
	}

	void displayMain() const
	{
		if (_main.empty())
		{
			std::cout << CYAN << "Main numbers: None" << RESET << std::endl;
			return;
		}

		std::cout << CYAN << "Main numbers: ";
		for (std::vector<Pair>::const_iterator it = _main.begin(); it != _main.end(); ++it)
		{
			std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << it->index << " " << RESET;
			for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
				std::cout << *vec_it << " ";
			if (it != _main.end() - 1)
				std::cout << YELLOW << " | ";
			std::cout << RESET;
		}
		std::cout << std::endl;
	}

	void displayPend() const
	{
		if (_pend.empty())
		{
			std::cout << CYAN << "Pend numbers: None" << RESET << std::endl;
			return;
		}
		std::cout << CYAN << "Pend numbers: ";
		for (std::vector<Pair>::const_iterator it = _pend.begin(); it != _pend.end(); ++it)
		{
			if (it != _pend.begin())
				std::cout << YELLOW << " | " << RESET;
			std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << it->index << " " << RESET;
			for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
				std::cout << *vec_it << " ";
			std::cout << RESET;
		}
		std::cout << std::endl;
	}

	void displayPair(const std::vector<Pair> &pairs) const
	{
		std::vector<Pair>::const_iterator it = pairs.begin();
		for (; it != pairs.end(); ++it)
		{
			if (it != pairs.begin())
				std::cout << YELLOW << " | " << RESET;
			std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << it->index << " " << RESET;
			for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
				std::cout << *vec_it << " ";
			std::cout << RESET;
		}
		std::cout << std::endl;
	}

	Container getNumbers() const
	{
		return _numbers;
	}
};

#endif