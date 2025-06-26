/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:58:51 by tsofien-          #+#    #+#             */
/*   Updated: 2025/06/26 15:18:25 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"
#include "utils.hpp"

// Steps :
// 1 . Parsing input of X numbers into a vector
// 2 . Making pair of numbers
// 3 . Sorting the pairs in ascending order
// 4 . Merge insertion sort the pairs into a single sorted vector

int main(int ac, char **av)
{
	if (ac != 1)
	{
		std::cerr << RED << "Usage: " << av[0] << RESET << std::endl;
		return 1;
	}

	Pmerge pmerge(ac, av);
	// 1 . Parsing input of X numbers into a vector

	return 0;
}
