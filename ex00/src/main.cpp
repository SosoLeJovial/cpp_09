/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:58:51 by tsofien-          #+#    #+#             */
/*   Updated: 2025/05/29 00:14:13 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "error" << std::endl;
		return 1;
	}

	std::string filename = av[1];
	// std::ofstream filename;
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return 1;
	}
	std::map<std::string, float> btContainer;

	std::string line;
	while (std::getline(file, line))
	{
		std::string date;
		float valueBtc;

		size_t pos = line.find(',');
		if (pos != std::string::npos)
		{
			date = line.substr(0, pos);
			valueBtc = atof(line.substr(pos + 1).c_str());
			btContainer.insert(std::make_pair(date, valueBtc));
		}
	}

	setColor(GREEN);
	std::cout << "Hello world!" << std::endl;
	resetColor();
	return 0;
}