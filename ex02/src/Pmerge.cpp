/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:07:10 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/16 10:55:56 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

Pmerge::Pmerge(/* args */)
{
}

Pmerge::Pmerge(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << RED << "Usage: " << av[0] << " <numbers>" << RESET << std::endl;
		throw std::invalid_argument("Invalid number of arguments");
	}

	std::vector<int> all_main;
	for (int i = 1; i < ac; i++)
	{
		if (!isValidInt(av[i]))
		{
			std::cerr << RED << "Error: Invalid input. Only integers are allowed." << RESET << std::endl;
			throw std::invalid_argument("Invalid input");
		}
		all_main.push_back(std::atoi(av[i]));
	}
	_main = all_main;
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

Pmerge::~Pmerge()
{
}

bool Pmerge::isDigit(const std::string &str) const
{
	if (str.empty())
		return false;

	size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
	for (size_t i = 0; i < start; i++)
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
	for (size_t i = 0; i < start; i++)
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

void Pmerge::sortVector()
{
	// step 1: make pairs of numbers and sort them

	size_t size = _main.size();
	size_t pairSize = 2;
	size_t levels = 0;

	displayVector();

	while (pairSize < size)
	{
		// Making pair
		for (size_t j = (pairSize / 2) - 1; j + (pairSize / 2) < size; j += pairSize)
		{
			// sort pair

			// std::cout << RESET << std::endl;
			// std::cout << CYAN << "Sorting pair: " << _main[j] << " and " << _main[j + (pairSize / 2)] << RESET << std::endl;
			// std::cout << GREEN << "Size pair: " << pairSize << RESET << std::endl;
			if (j < size && j + (pairSize / 2) < size && _main[j] > _main[j + (pairSize / 2)])
			{
				for (size_t k = j - (pairSize / 2) + 1; k <= j; k++)
				{
					// std::cout << "Swap " << _main[k] << " and " << _main[k + (pairSize / 2)] << std::endl;
					std::swap(_main[k], _main[k + (pairSize / 2)]);
				}
			}
		}
		pairSize *= 2;
		levels++;
	}

	_rest.clear();
	_pend.clear();
	displayVector();

	std::vector<Pair> pairs;
	makePairs(pairs, 2);
	displayPair(pairs);
}

void Pmerge::displayVector() const
{

	std::cout << CYAN << "Main numbers: ";
	for (std::vector<int>::const_iterator it = _main.begin(); it != _main.end(); ++it)
	{
		std::cout << BLUE << *it << " ";
	}
	std::cout << std::endl;
	if (!_pend.empty())
	{
		std::cout << GREEN << "Pend numbers: ";
		for (std::vector<int>::const_iterator it = _pend.begin(); it != _pend.end(); ++it)
		{
			std::cout << GREEN << *it << " ";
		}
		std::cout << std::endl;
	}
	if (!_rest.empty())
	{
		std::cout << YELLOW << "Rest numbers: ";
		for (std::vector<int>::const_iterator it = _rest.begin(); it != _rest.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << RESET << std::endl;
	}
}

void Pmerge::displayPair(std::vector<Pair> &pairs) const
{
	std::cout << MAGENTA << "Pairs: " << RESET << std::endl;
	std::vector<Pair>::const_iterator it = pairs.begin();
	for (; it != pairs.end(); ++it)
	{
		std::cout << GREEN << "Index: " << it->index << " | Type: " << (it->pair_type == A ? "A" : "B") << " | Pair: " << BLUE;
		for (std::vector<int>::const_iterator vec_it = it->pair.begin(); vec_it != it->pair.end(); ++vec_it)
		{
			std::cout << *vec_it << " ";
		}
		std::cout << RESET << std::endl;
	}
}

void Pmerge::makePairs(std::vector<Pair> &pairs, size_t pairSize)
{
	size_t size = _main.size();

	for (size_t i = 0; i < size; i += pairSize)
	{
		if (i + pairSize > size)
			break;

		size_t pair_number = i / pairSize;
		type pair_side = pair_number % 2 ? B : A;
		size_t index = pair_number / 2 + 1;

		std::vector<int> _numbers(_main.begin() + i, _main.begin() + i + pairSize);
		Pair new_pair = {index, pair_side, _numbers};
		pairs.push_back(new_pair);
	}
}
