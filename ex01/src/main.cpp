/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:57:48 by tsofien-          #+#    #+#             */
/*   Updated: 2025/05/21 23:55:07 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "utils.hpp"

int main()
{
	setColor(GREEN);
	std::cout << "Hello world!" << std::endl;
	resetColor();
	return 0;
}
