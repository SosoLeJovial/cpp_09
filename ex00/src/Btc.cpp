/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Btc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:48:48 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/27 09:26:05 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Btc.hpp"
#include <sstream>

/* ************************************************************************** */
/*                           CONSTRUCTORS & DESTRUCTOR                       */
/* ************************************************************************** */

/**
 * @brief Constructor that loads Bitcoin data from CSV file and processes input file
 * @param fileData Path to the CSV file containing Bitcoin exchange rates
 * @param input Path to the input file containing dates and values to process
 */
Btc::Btc(std::string &fileData, std::string &input)
{
	std::ifstream file(fileData.c_str());
	if (!file.is_open())
	{
		std::cout << RED << "Error: Could not open file " << fileData << RESET << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos != std::string::npos)
		{
			std::string date = line.substr(0, pos);
			std::stringstream ss(line.substr(pos + 1));
			float value;
			ss >> value;

			dataCsv.insert(std::make_pair(date, value));
		}
	}
	file.close();

	std::ifstream fileInput(input.c_str());
	if (!fileInput.is_open())
	{
		std::cout << RED << "Error: Could not open input " << input << RESET << std::endl;
		return;
	}

	std::string lineInput;
	while (std::getline(fileInput, lineInput))
	{
		if (lineInput.empty() || isEmptyLine(lineInput))
			continue;
		parseInput(lineInput);
	}
	fileInput.close();
}

/**
 * @brief Copy constructor
 * @param src Source object to copy from
 */
Btc::Btc(const Btc &src)
{
	if (this != &src)
		dataCsv = src.dataCsv;
}

/**
 * @brief Assignment operator
 * @param rhs Right-hand side object to assign from
 * @return Reference to this object
 */
Btc &Btc::operator=(const Btc &rhs)
{
	if (this != &rhs)
		dataCsv = rhs.dataCsv;
	return *this;
}

/**
 * @brief Destructor
 */
Btc::~Btc() {}

/* ************************************************************************** */
/*                              PARSING METHODS                              */
/* ************************************************************************** */

/**
 * @brief Parse a single line from input file and validate format
 * @param input Line to parse (format: "date | value")
 */
void Btc::parseInput(std::string &input)
{
	std::string line = trim(input);
	if (line == "date|value")
		return;

	size_t pos = line.find("|");

	std::string date = line.substr(0, pos);
	if (!validDate(date))
	{
		std::cout << RED << "Error: bad input => " << date << RESET << std::endl;
		return;
	}

	std::string valueStr = line.substr(pos + 1);
	if (!validValue(valueStr))
		return;
	float value = std::atof(valueStr.c_str());

	std::cout << GREEN << date << " => " << value << " = " << value * getBitcoinPrice(date) << RESET << std::endl;
}

bool Btc::isEmptyLine(const std::string &line)
{
	for (size_t i = 0; i < line.length(); ++i)
	{
		if (!std::isspace(line[i]))
			return false;
	}
	return true;
}

/* ************************************************************************** */
/*                            VALIDATION METHODS                             */
/* ************************************************************************** */

/**
 * @brief Validate date format (YYYY-MM-DD)
 * @param date Date string to validate
 * @return true if date format is valid, false otherwise
 */
bool Btc::validDate(const std::string &date)
{
	if (date.length() != 10)
		return false;

	if (date[4] != '-' || date[7] != '-')
		return false;

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	if (!isDigitStr(yearStr) || !isDigitStr(monthStr) || !isDigitStr(dayStr))
		return false;

	int year, month, day;
	if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3)
		return false;

	if (month < 1 || month > 12)
		return false;

	int daysInMonth[12] = {31, 28, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31};

	if (month == 2 && isLeapYear(year))
		return day >= 1 && day <= 29;

	if (day >= 1 && day <= daysInMonth[month - 1])
		return true;

	return false;
}

bool Btc::validValue(const std::string &value)
{
	if (!isDigitStr(value))
	{
		std::cout << RED << "Error: Value must be a digit." << RESET << std::endl;
		return false;
	}

	float c = std::atof(value.c_str());

	if (c < 0)
	{
		std::cout << RED << "Error: not a positive number." << RESET << std::endl;
		return false;
	}

	if (c > std::numeric_limits<float>::max() || c >= std::numeric_limits<int>::max())
	{
		std::cout << RED << "Error: too large number." << RESET << std::endl;
		return false;
	}
	return true;
}

/**
 * @brief Check if a string contains only digits
 * @param s String to check
 * @return true if string contains only digits, false otherwise
 */
bool Btc::isDigitStr(const std::string &s)
{
	int signCount = 0;

	for (std::size_t i = 0; i < s.length(); ++i)
	{
		if (s[i] == '-' || s[i] == '+')
		{
			signCount++;
			if (signCount > 1 || i > 0)
				return false;
			continue;
		}
		if (s[i] == '.')
		{
			if (signCount > 0)
				return false;
			continue;
		}
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

bool Btc::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/* ************************************************************************** */
/*                               GETTERS                                     */
/* ************************************************************************** */

/**
 * @brief Get reference to the Bitcoin data map
 * @return Const reference to the data map
 */
const std::map<std::string, float> &Btc::getDataCsv() const
{
	return dataCsv;
}

/* ************************************************************************** */
/*                             DEBUG METHODS                                 */
/* ************************************************************************** */

/**
 * @brief Print all loaded Bitcoin data for debugging purposes
 */
void Btc::printData() const
{
	std::map<std::string, float>::const_iterator it = this->dataCsv.begin();
	while (it != this->dataCsv.end())
	{
		std::cout << it->first << " => " << it->second << std::endl;
		it++;
	}
}

float Btc::getBitcoinPrice(const std::string &date)
{
	std::map<std::string, float>::iterator it = this->dataCsv.lower_bound(date);

	if (it != this->dataCsv.end())
		return it->second;
	return -1;
}
