/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rpn.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:20:03 by tsofien-          #+#    #+#             */
/*   Updated: 2025/05/22 00:29:49 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Rpn.hpp"
#include <cctype>
#include <sstream>

Rpn::Rpn() {}

Rpn::Rpn(const Rpn &other) : _stack(other._stack) {}

Rpn &Rpn::operator=(const Rpn &other)
{
	if (this != &other)
	{
		_stack = other._stack;
	}
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
		_stack.push(a + b);
		break;
	case '-':
		_stack.push(a - b);
		break;
	case '*':
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