/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:07:10 by tsofien-          #+#    #+#             */
/*   Updated: 2025/06/26 15:26:25 by tsofien-         ###   ########.fr       */
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

	for (int i = 1; i < ac; ++i)
	{
		if (!isValidInt(av[i]))
		{
			std::cerr << RED << "Error: Invalid input. Only digits are allowed." << RESET << std::endl;
			throw std::invalid_argument("Invalid input");
		}
		if (i == 1 && (i % 2 == 0))
			continue;
		else
		{
			Pair pair;
			pair.first = std::stoi(av[i - 1]);
			pair.second = std::stoi(av[i]);
			_numbers.push_back(pair);
		}
		if (ac % 2 == 1)
		{
			Pair pair;
			pair.first = std::stoi(av[ac]);
			pair.second = 0;
			_numbers.push_back(pair);
		}
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