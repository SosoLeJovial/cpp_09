/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:48:59 by tsofien-          #+#    #+#             */
/*   Updated: 2025/05/31 00:22:23 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
#define BTC_HPP

#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <limits>
#include <iomanip>

class Btc
{
private:
	std::map<std::string, float> dataCsv;
	std::string date;
	float value;
	Btc();

public:
	Btc(std::string &fileData, std::string &input);
	Btc(const Btc &src);
	Btc &operator=(const Btc &rhs);
	~Btc();

	// getters
	const std::map<std::string, float> &getDataCsv() const;

	// Member functions
	void parseInput(std::string &input);
	bool validDate(const std::string &date);
	bool isLeapYear(int year);
	bool isDigitStr(const std::string &s);
	bool isEmptyLine(const std::string &line);
	bool validValue(const std::string &value);
	float getBitcoinPrice(const std::string &date);
	void printData() const;
};

#endif
