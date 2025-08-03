/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:48:48 by tsofien-          #+#    #+#             */
/*   Updated: 2025/08/03 16:35:02 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* ************************************************************************** */
/*                           CONSTRUCTORS & DESTRUCTOR                       */
/* ************************************************************************** */

BitcoinExchange::BitcoinExchange(std::string &fileData, std::string &input)
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

			_dataCsv.insert(std::make_pair(date, value));
		}
	}
	file.close();

	if (_dataCsv.empty())
	{
		std::cout << RED << "Error: " << fileData << " is empty." << RESET << std::endl;
		return;
	}

	if (fileEmpty(input))
	{
		std::cout << RED << "Error: " << input << " is empty." << RESET << std::endl;
		return;
	}

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

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	if (this != &src)
		_dataCsv = src._dataCsv;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
		_dataCsv = rhs._dataCsv;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/* ************************************************************************** */
/*                               GETTERS                                     */
/* ************************************************************************** */

const std::map<std::string, double> &BitcoinExchange::getDataCsv() const
{
	return _dataCsv;
}

/* ************************************************************************** */
/*                              PARSING METHODS                              */
/* ************************************************************************** */

bool BitcoinExchange::isDigitStr(const std::string &s)
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

bool BitcoinExchange::isEmptyLine(const std::string &line)
{
	for (size_t i = 0; i < line.length(); ++i)
	{
		if (!std::isspace(line[i]))
			return false;
	}
	return true;
}

bool BitcoinExchange::validValue(const std::string &value)
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

bool BitcoinExchange::fileEmpty(const std::string inputFile)
{
	std::ifstream fileInput(inputFile.c_str());
	if (!fileInput.is_open())
	{
		std::cout << RED << "Error: Could not open input " << inputFile << RESET << std::endl;
		return false;
	}

	std::string lineInput;

	while (std::getline(fileInput, lineInput))
	{
		if (lineInput.empty() || isEmptyLine(lineInput))
			continue;
		else
			return false;
	}

	fileInput.close();
	return true;
}

/* ************************************************************************** */
/*                            VALIDATION METHODS                             */
/* ************************************************************************** */

void BitcoinExchange::parseInput(std::string &input)
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
	double value = strtod(valueStr.c_str(), NULL);

	if (value < 0 || value > 1000)
	{
		std::cout << RED << "Error: value must be between 0 and 1000" << RESET << std::endl;
		return;
	}
	if (getBitcoinPrice(date) == -1)
		return;

	std::cout << GREEN << date << " => " << value << " = " << std::fixed << std::setprecision(2) << value * getBitcoinPrice(date) << std::fixed << std::setprecision(0) << RESET << std::endl;
}

bool BitcoinExchange::validDate(const std::string &date)
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

bool BitcoinExchange::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void BitcoinExchange::fillDate(const std::string &date, long &dateLong) {
    int year, month, day;
    if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3) {
        dateLong = -1;
        return;
    }
    dateLong = year * 10000 + month * 100 + day;
}

double BitcoinExchange::getBitcoinPrice(const std::string &date)
{
    if (_dataCsv.empty()) {
        std::cerr << "Error: No data available" << std::endl;
        return -1;
    }

    std::map<std::string, double>::iterator it = _dataCsv.lower_bound(date);
    
    if (it == _dataCsv.end()) {
        return (--it)->second;
    }
    
    if (it->first == date) {
        return it->second;
    }
    
    if (it == _dataCsv.begin()) {
        std::cerr << RED << "Error: Date " << date << " is before first available data" << RESET << std::endl;
        return -1;
    }
    
    std::map<std::string, double>::iterator prevIt = it;
	if (prevIt != _dataCsv.begin())
		--prevIt;
	else
		return it->second;
    
    long targetDate, postDate, preDate;
    fillDate(date, targetDate);
    fillDate(it->first, postDate);
    fillDate(prevIt->first, preDate);

	if (targetDate == -1 || postDate == -1 || preDate == -1) {
		std::cerr << RED << "Error: Invalid date format" << RESET << std::endl;
		return -1;
	}
    
    long diffPost = abs(postDate - targetDate);
    long diffPre = abs(preDate - targetDate);
    
    return (diffPre <= diffPost) ? prevIt->second : it->second;
}
/* ************************************************************************** */