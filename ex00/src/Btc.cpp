/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Btc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:48:48 by tsofien-          #+#    #+#             */
/*   Updated: 2025/05/30 01:25:45 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Btc.hpp"
#include <sstream>

Btc::Btc(const std::string &fileData, const std::string &input)
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
			dataCsv.insert({date, value});
		}
	}
	file.close();
}

Btc::Btc(const Btc &src)
{
	if (this != &src)
		dataCsv = src.dataCsv;
}

Btc &Btc::operator=(const Btc &rhs)
{

	if (this != &rhs)
		dataCsv = rhs.dataCsv;
	return *this;
}

Btc::~Btc() {}

void Btc::parseInput(std::string &input)
{
	trim(input); // Trim whitespace from the input string
	size_t pos = input.find(" | ");
	if (pos == std::string::npos)
	{
		std::cout << RED << "Error: Invalid input format. Expected format: 'date | value'" << RESET << std::endl;
		return;
	}
	std::string date = input.substr(0, pos);
	if (!validDate(date))
	{
		std::cout << RED << "Error: Invalid date format. Expected format: 'YYYY-MM-DD" << RESET << std::endl;
		return;
	}
	// valueStr is pos until the end of the string
	std::string valueStr = input.substr(pos + 3);
}

// void Btc::loadData()
// {
// }

// void Btc::printInput() const
// {
// }

// void Btc::printData() const
// {
// }

// Getters
const std::map<std::string, float> &Btc::getDataCsv() const
{
	return dataCsv;
}

// print method for debugging
void Btc::printData() const
{
	std::map<std::string, float>::const_iterator it = this->dataCsv.begin();
	while (it != this->dataCsv.end())
	{
		std::cout << it->first << " => " << it->second << std::endl;
		it++;
	}
}