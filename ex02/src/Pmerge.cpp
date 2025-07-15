/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:07:10 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/15 13:21:08 by tsofien-         ###   ########.fr       */
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
	size_t pairSize = 1;
	size_t levels = 0;

	for (size_t i = 0; i < size; i += pairSize * 2)
	{
		std::cout << PINK << "levels: " << levels << RESET << std::endl;
		for (size_t j = i; j + pairSize < size; j += pairSize * 2)
		{
			if (j + pairSize >= size)
				break;
			std::cout << RED << "Pair: ";
			for (size_t k = 0; k < pairSize; k++)
			{
				std::cout << _main[j + k] << " ";
			}
			std::cout << "and ";
			for (size_t k = 0; k < pairSize; k++)
			{
				std::cout << _main[j + pairSize + k] << " ";
			}
			std::cout << RESET << std::endl;
			std::cout << CYAN << "Sorting pair: " << _main[j] << " and " << _main[j + pairSize] << RESET << std::endl;
			if (_main[j] > _main[j + pairSize])
			{
				for (size_t k = 0; k < pairSize; k++)
				{
					std::swap(_main[j + k], _main[j + pairSize + k]);
				}
			}
			std::cout << RED << "j: " << j << RESET << std::endl;
			displayVector();
			std::cout << std::endl;
		}
		std::cout << std::endl
				  << std::endl;
		pairSize *= 2;
		levels++;
	}

	std::cout << PINK << "levels: " << levels << RESET << std::endl;

	_rest.clear();
	_pend.clear();
	// step 2: insertion in pend

	size_t i = 0;

	pairSize = 1;
	for (; i < size; i += 2)
	{
		if (i + 1 < size)
		{
			_pend.push_back(_main[i + pairSize]);
		}
	}
	displayVector();
	for (; i < size; i++)
	{
		_rest.push_back(_main[i]);
	}
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
