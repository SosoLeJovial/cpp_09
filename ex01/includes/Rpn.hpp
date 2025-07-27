/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:15:03 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/27 10:18:18 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include "utils.hpp"
#include <string>
#include <stdexcept>

class Rpn
{
private:
	std::stack<int> _stack;

	bool isOperator(char c) const;
	bool isDigit(char c) const;
	void performOperation(char op);
	bool checkOverflow(int a, int b, char op);
	
	public:
	Rpn();
	Rpn(const Rpn &src);
	Rpn &operator=(const Rpn &rhs);
	~Rpn();

	int calculate(const std::string &expression);

	class InvalidExpressionException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class DivisionByZeroException : public std::exception
	{
	public:
		const char *what() const throw();
	};
};

#endif
