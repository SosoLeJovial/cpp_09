/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:07:10 by tsofien-          #+#    #+#             */
/*   Updated: 2025/06/29 03:44:05 by tsofien-         ###   ########.fr       */
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

	std::vector<int> all_numbers;
	for (int i = 1; i < ac; i++)
	{
		if (!isValidInt(av[i]))
		{
			std::cerr << RED << "Error: Invalid input. Only integers are allowed." << RESET << std::endl;
			throw std::invalid_argument("Invalid input");
		}
		std::cout << GREEN << "Input: " << av[i] << RESET << std::endl;
		all_numbers.push_back(std::atoi(av[i]));
	}
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

	// Vérifier l'overflow avec strtol
	char *endptr;
	errno = 0;
	long val = std::strtol(str.c_str(), &endptr, 10);

	// Vérifier si conversion complète et pas d'overflow
	return (errno != ERANGE && *endptr == '\0' &&
			val >= std::numeric_limits<int>::min() &&
			val <= std::numeric_limits<int>::max());
}

void Pmerge::sortVector()
{
	size_t size = _numbers.size();
	size_t pairSize = 1;

	for (size_t i = 0; i < size; i += pairSize * 2)
	{
		size_t mid = std::min(i + pairSize, size);
		size_t end = std::min(i + pairSize * 2, size);

		std::inplace_merge(_numbers.begin() + i, _numbers.begin() + mid, _numbers.begin() + end);
		pairSize *= 2;
	}
}

void Pmerge::displayVector() const
{
	if (_numbers.empty())
	{
		std::cout << "No numbers to display." << std::endl;
		return;
	}

	std::cout << "Sorted numbers: ";
	for (std::vector<int>::const_iterator it = _numbers.begin(); it != _numbers.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
