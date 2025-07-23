/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:58:51 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/24 00:13:57 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"
#include "utils.hpp"

int main(int ac, char **av)
{
	if (ac <= 1)
	{
		std::cerr << RED << "Usage: " << av[0] << RESET << std::endl;
		return 1;
	}

	try
	{
		// Example with std::vector<int>
		std::cout << YELLOW << "=== SORTING WITH VECTOR ===" << RESET << std::endl;
		Pmerge pmerge_vector(ac, av);
		pmerge_vector.sort();
		pmerge_vector.displayNumbers();
		if (pmerge_vector.is_sort(pmerge_vector.getNumbers()))
		{
			std::cout << GREEN << "The numbers are sorted correctly." << RESET << std::endl;
		}
		else
		{
			std::cerr << RED << "Error: The numbers are not sorted correctly." << RESET << std::endl;
			return 1;
		}
		std::cout << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	// size_t currentLimit = 1;
	// int jcb_start = 0;
	// while (currentLimit < 1000)
	// {
	// 	currentLimit = Pmerge::jacobstahl_numbers(jcb_start);
	// 	std::cout << GREEN << "Current limit: " << currentLimit << RESET << std::endl;
	// 	jcb_start++;
	// }

	return 0;
}
