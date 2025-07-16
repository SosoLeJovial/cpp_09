/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:58:51 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/16 14:50:14 by tsofien-         ###   ########.fr       */
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
		
		std::cout << std::endl;
		
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
