/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:50:42 by tsofien-          #+#    #+#             */
/*   Updated: 2025/06/26 15:19:07 by tsofien-         ###   ########.fr       */
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

typedef struct Pair
{
	int first;
	int second;
} Pair;

class Pmerge
{
private:
	std::vector<Pair> _numbers;

public:
	Pmerge(/* args */);
	Pmerge(int ac, char **av);
	Pmerge(const Pmerge &src);
	Pmerge &operator=(const Pmerge &rhs);
	~Pmerge();

	// utility functions
	bool isDigit(const std::string &str) const;
	bool isValidInt(const std::string &str) const;
};

#endif