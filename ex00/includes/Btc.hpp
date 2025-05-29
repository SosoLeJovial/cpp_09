/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:48:59 by tsofien-          #+#    #+#             */
/*   Updated: 2025/05/30 01:17:03 by tsofien-         ###   ########.fr       */
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

class Btc
{
private:
	std::map<std::string, float> dataCsv;
	std::string date;
	float value;
	Btc();

public:
	Btc(const std::string &fileData, const std::string &input);
	Btc(const Btc &src);
	Btc &operator=(const Btc &rhs);
	~Btc();

	// getters
	const std::map<std::string, float> &getDataCsv() const;

	// Member functions
	void parseInput(std::string &input);
	bool validDate(const std::string &date);
	bool validValue(float value);

	// void loadData();
	// void printInput() const;
	void printData() const;
};

#endif
