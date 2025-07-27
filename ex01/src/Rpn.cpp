/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:20:03 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/27 10:25:36 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Rpn.hpp"
#include <cctype>
#include <sstream>
#include <limits>

Rpn::Rpn() {}

Rpn::Rpn(const Rpn &src) : _stack(src._stack) {}

Rpn &Rpn::operator=(const Rpn &rhs)
{
	if (this != &rhs)
		_stack = rhs._stack;
	return *this;
}

Rpn::~Rpn() {}

bool Rpn::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool Rpn::isDigit(char c) const
{
	return (c >= '0' && c <= '9');
}

bool Rpn::checkOverflow(int a, int b, char op)
{
	switch (op)
	{
	case '+':
		if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
			(b < 0 && a < std::numeric_limits<int>::min() - b))
			return true;
		break;
	case '-':
		if ((b > 0 && a < std::numeric_limits<int>::min() + b) ||
			(b < 0 && a > std::numeric_limits<int>::max() + b))
			return true;
		break;
	case '*':
		if (a != 0 && b != 0 && (a > std::numeric_limits<int>::max() / b || a < std::numeric_limits<int>::min() / b))
			return true;
		break;
	case '/':
		if (b == 0)
			return true;
		break;
	}
	return false;
}

void Rpn::performOperation(char op)
{
	if (_stack.size() < 2)
		throw InvalidExpressionException();

	int b = _stack.top();
	_stack.pop();
	int a = _stack.top();
	_stack.pop();

	switch (op)
	{
	case '+':
		if (checkOverflow(a, b, op))
			throw InvalidExpressionException();
		_stack.push(a + b);
		break;
	case '-':
		if (checkOverflow(a, b, op))
			throw InvalidExpressionException();
		_stack.push(a - b);
		break;
	case '*':
		if (checkOverflow(a, b, op))
			throw InvalidExpressionException();
		_stack.push(a * b);
		break;
	case '/':
		if (b == 0)
			throw DivisionByZeroException();
		_stack.push(a / b);
		break;
	}
}

int Rpn::calculate(const std::string &expression)
{
	while (!_stack.empty())
		_stack.pop();

	std::istringstream iss(expression);
	std::string token;


	while (iss >> token)
	{
		if (token.length() == 1)
		{
			char c = token[0];

			if (isDigit(c))
				_stack.push(c - '0');
			else if (isOperator(c))
				performOperation(c);
			else
				throw InvalidExpressionException();
		}
		else
			throw InvalidExpressionException();
	}

	if (_stack.size() != 1)
		throw InvalidExpressionException();

	return _stack.top();
}

// Exception classes
const char *Rpn::InvalidExpressionException::what() const throw()
{
	return "Error: Invalid RPN expression";
}

const char *Rpn::DivisionByZeroException::what() const throw()
{
	return "Error: Division by zero";
}