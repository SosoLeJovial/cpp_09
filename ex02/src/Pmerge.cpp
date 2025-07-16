/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:41:26 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/16 17:41:17 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

// ========================================================================
// CONSTRUCTORS AND DESTRUCTOR
// ========================================================================

Pmerge::Pmerge(int ac, char **av)
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
	{
		_numbers.push_back(all_numbers[i]);
	}
	std::cout << GREEN << "Numbers to sort: " << ac - 1 << RESET << std::endl;
}
Pmerge::Pmerge(const Pmerge &src)
{
	(void)src;
}

Pmerge &Pmerge::operator=(const Pmerge &rhs)
{
	(void)rhs;
	return *this;
}

Pmerge::~Pmerge() {};

// ========================================================================
// PARSING AND VALIDATION FUNCTIONS
// ========================================================================

bool Pmerge::isDigit(const std::string &str) const
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

bool Pmerge::isValidInt(const std::string &str) const
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

// ========================================================================
// SORTING FUNCTIONS (FORD-JOHNSON ALGORITHM)
// ========================================================================

void Pmerge::sort()
{
	std::vector<Pair> pairs;
	int stragglers = -1;

	if (_numbers.size() % 2 != 0)
	{
		stragglers = _numbers.back();
		_numbers.pop_back();
	}
	size_t pairSize = createPairs();
	makePairs(pairs, pairSize);

// Display the initial state of the numbers and pairs
#ifdef DEBUG
	displayNumbers();
#endif
	recursivePairs(pairs, pairSize / 2);
}

size_t Pmerge::createPairs()
{
	size_t size = _numbers.size();
	size_t pairSize = 2;
	size_t levels = 0;

	while (pairSize < size)
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
	return pairSize / 2;
}

void Pmerge::makePairs(std::vector<Pair> &pairs, size_t pairSize)
{
	pairs.clear();
	size_t size = _numbers.size();

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

void Pmerge::recursivePairs(std::vector<Pair> &pairs, size_t pairSize)

{
	if (pairSize < 1)
		return;
	_main.clear();
	_pend.clear();
	_rest.clear();
	// push the rest in rest container
	size_t restIndex = _numbers.size() % pairSize;
	size_t sizeNumbers = _numbers.size();
	for (size_t i = sizeNumbers - 1; i >= sizeNumbers - restIndex; i--)
	{
		_rest.push_back(_numbers[i]);
		_numbers.pop_back();
	}
#ifdef DEBUG

	displayRest();
#endif
	// push all b1 b2 b3 b4 ect in pend and an in main
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
	displayMain();
	displayPend();
#endif

	// insert with Jacob-Stahl sequence
	for (std::vector<Pair>::const_iterator it = _pend.begin(); it != _pend.end(); ++it)
		_main.push_back(*it);

	// push all in numbers and repeat
	_numbers.clear();
	for (std::vector<Pair>::const_iterator it = _main.begin(); it != _main.end(); ++it)
	{
		for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
		{
			_numbers.push_back(*vec_it);
		}
	}
	displayNumbers();
	makePairs(pairs, pairSize / 2);
	recursivePairs(pairs, pairSize / 2);
}

// ========================================================================
// DISPLAY AND DEBUG FUNCTIONS
// ========================================================================

void Pmerge::displayNumbers() const
{
	std::cout << YELLOW << "Display numbers: ";
	for (std::vector<int>::const_iterator it = _numbers.begin(); it != _numbers.end(); ++it)
	{
		std::cout << BLUE << *it << " ";
	}
	std::cout << RESET << std::endl;
}

void Pmerge::displayRest() const
{
	std::cout << CYAN << "Rest numbers: ";
	for (std::vector<int>::const_iterator it = _rest.begin(); it != _rest.end(); ++it)
	{
		std::cout << BLUE << *it << " ";
	}
	std::cout << RESET << std::endl;
}

void Pmerge::displayMain() const
{
	if (_main.empty())
	{
		std::cout << CYAN << "Main numbers: None" << RESET << std::endl;
		return;
	}
	{
		/* code */
	}

	std::cout << CYAN << "Main numbers: ";
	for (std::vector<Pair>::const_iterator it = _main.begin(); it != _main.end(); ++it)
	{
		std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << BLUE << it->index << " ";
		for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
		{
			std::cout << *vec_it << " ";
		}
		std::cout << YELLOW << " | ";
		std::cout << RESET;
	}
	std::cout << std::endl;
}

void Pmerge::displayPend() const
{
	if (_pend.empty())
	{
		std::cout << CYAN << "Pend numbers: None" << RESET << std::endl;
		return;
	}
	std::cout << CYAN << "Pend numbers: ";
	for (std::vector<Pair>::const_iterator it = _pend.begin(); it != _pend.end(); ++it)
	{
		std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << BLUE << it->index << " ";
		for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
		{
			std::cout << *vec_it << " ";
		}
		std::cout << YELLOW << " | ";
		std::cout << RESET;
	}
	std::cout << std::endl;
}

void Pmerge::displayPair(const std::vector<Pair> &pairs) const
{
	std::vector<Pair>::const_iterator it = pairs.begin();
	for (; it != pairs.end(); ++it)
	{
		std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << it->index << " " << BLUE;
		for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
		{
			std::cout << *vec_it << " ";
		}
		std::cout << YELLOW << " | ";
		std::cout << RESET;
	}
	std::cout << std::endl;
}

/* ************************************************************************** */
