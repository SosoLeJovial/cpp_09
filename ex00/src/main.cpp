/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:58:51 by tsofien-          #+#    #+#             */
/*   Updated: 2025/08/02 22:47:37 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Btc.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << RED << "Usage: " << av[0] << " \"fileToCheck\"" << RESET << std::endl;
		return 1;
	}
	std::string filename = av[1];
	std::string fileData = "data.csv";
	Btc btc(fileData, filename);

	// std::string fileError = "file_do_not_exist.jsp";
	// Btc error(fileError, filename);

	return 0;
}