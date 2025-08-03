/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:48:59 by tsofien-          #+#    #+#             */
/*   Updated: 2025/08/03 16:32:36 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

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
#include <sstream>
#include <iomanip>

class BitcoinExchange
{
private:
	std::map<std::string, double> _dataCsv;
	std::string date;
	double value;
	BitcoinExchange();

public:
/* ************************************************************************** */
/*                           CONSTRUCTORS & DESTRUCTOR                       */
/* ************************************************************************** */
	BitcoinExchange(std::string &fileData, std::string &input);
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);
	~BitcoinExchange();

/* ************************************************************************** */
/*                               GETTERS                                     */
/* ************************************************************************** */
	const	std::map<std::string, double> &getDataCsv() const;

/* ************************************************************************** */
/*                              PARSING METHODS                              */
/* ************************************************************************** */
	bool	isDigitStr(const std::string &s);
	bool	isEmptyLine(const std::string &line);
	bool	validValue(const std::string &value);
	bool	fileEmpty(const std::string inputFile);
	
/* ************************************************************************** */
/*                            VALIDATION METHODS                             */
/* ************************************************************************** */
	void	parseInput(std::string &input);
	bool	validDate(const std::string &date);
	bool	isLeapYear(int year);
	void	fillDate(const std::string &date, long &dateLong);
	double	getBitcoinPrice(const std::string &date);

};

#endif
