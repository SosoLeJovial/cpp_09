/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:50:42 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/15 17:44:45 by tsofien-         ###   ########.fr       */
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

class Pmerge
{
private:
	std::vector<int> _pend;
	std::vector<int> _main;
	std::vector<int> _rest;

public:
	Pmerge(/* args */);
	Pmerge(int ac, char **av);
	Pmerge(const Pmerge &src);
	Pmerge &operator=(const Pmerge &rhs);
	~Pmerge();

	// getters

	// utility functions
	bool isDigit(const std::string &str) const;
	bool isValidInt(const std::string &str) const;

	// sorting functions
	void sortVector();
	void displayVector() const;
	void displayPair(size_t pairSize) const;
	// void sortDeque();
};

#endif