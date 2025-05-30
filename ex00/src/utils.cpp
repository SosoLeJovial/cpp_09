/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:37:55 by tsofien-          #+#    #+#             */
/*   Updated: 2025/05/30 18:04:58 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <algorithm>

void setColor(std::string color)
{
	std::cout << color;
}

void resetColor()
{
	std::cout << RESET;
}

std::string trim(const std::string &str)
{
	std::string result = str;
	result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
	return result;
}
