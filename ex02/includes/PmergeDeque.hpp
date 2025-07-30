/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeDeque.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:50:42 by tsofien-          #+#    #+#             */
/*   Updated: 2025/07/30 14:27:59 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEDEQUE_HPP
#define PMERGEDEQUE_HPP

#include "PmergeVector.hpp"
#include <deque>

struct PairDeque
{
	size_t index;
	type pair_type;
	std::deque<int> pairDeque;
};

class PmergeDeque
{
private:
	struct timeval start, end;
	int jcb_start;
	std::deque<int> _numbers;
	std::deque<PairDeque> _main;
	std::deque<int> _rest;
	std::deque<PairDeque> _pend;

	PmergeDeque(/* args */);

public:
	// ========================================================================
	// CONSTRUCTORS AND DESTRUCTOR
	// ========================================================================
	PmergeDeque(int ac, char **av)
	{
		if (ac < 2)
		{
			std::cerr << RED << "Usage: " << av[0] << " <numbers>" << RESET << std::endl;
			throw std::invalid_argument("Invalid number of arguments");
		}
		std::deque<int> all_numbers;
		for (int i = 1; i < ac; i++)
		{
			if (!isValidInt(av[i]))
			{
				std::cerr << RED << "Error: Invalid input. Only integers are allowed." << RESET << std::endl;
				throw std::invalid_argument("Invalid input");
			}
			all_numbers.push_back(std::atoi(av[i]));
		}
		for (size_t i = 0; i < all_numbers.size(); i++)
			_numbers.push_back(all_numbers[i]);
		std::cout << GREEN << "Before: " << RESET;
		displayNumbers();
	}

	PmergeDeque(const PmergeDeque &src)
	{
		if (this != &src)
		{
			jcb_start = src.jcb_start;
			_numbers = src._numbers;
			_main = src._main;
			_rest = src._rest;
			_pend = src._pend;
		}
	}

	PmergeDeque &operator=(const PmergeDeque &rhs)
	{
		if (this != &rhs)
		{
			jcb_start = rhs.jcb_start;
			_numbers = rhs._numbers;
			_main = rhs._main;
			_rest = rhs._rest;
			_pend = rhs._pend;
		}
		return *this;
	}

	~PmergeDeque() {};
	// ========================================================================
	// PARSING AND VALIDATION FUNCTIONS
	// ========================================================================

	bool isDigit(const std::string &str) const
	{
		if (str.empty())
			return false;
		size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		for (size_t i = start; i < str.length(); i++)
		{
			if (!std::isdigit(str[i]))
				return false;
		}
		return true;
	}

	bool isValidInt(const std::string &str) const
	{
		if (str.empty() || str[0] == '-' || str[0] == '+')
			return false;

		size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
		for (size_t i = start; i < str.length(); i++)
		{
			if (!std::isdigit(str[i]))
				return false;
		}

		char *endptr;
		errno = 0;
		long val = std::strtol(str.c_str(), &endptr, 10);

		return (errno != ERANGE && *endptr == '\0' &&
				val >= std::numeric_limits<int>::min() &&
				val <= std::numeric_limits<int>::max());
	}

	bool has_duplicates(const std::deque<int> &vec)
	{
		std::deque<int> seen;
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (std::find(seen.begin(), seen.end(), vec[i]) != seen.end())
				return true;
			seen.push_back(vec[i]);
		}
		return false;
	}

	bool is_sort(std::deque<int> &vec)
	{

		for (std::deque<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
		{
			if (it + 1 != vec.end() && *it > *(it + 1))
				return false;
		}
		return true;
	}

	// ========================================================================
	// SORTING FUNCTIONS (FORD-JOHNSON ALGORITHM)
	// ========================================================================

	void sort()
	{
		gettimeofday(&start, NULL);
		std::deque<PairDeque> PairDeques;
		int stragglers = -1;

		if (has_duplicates(_numbers))
		{
			std::cerr << RED << "Error: Duplicate found." << RESET << std::endl;
			throw std::invalid_argument("Invalid number: duplicate");
		}

		if (is_sort(_numbers))
		{
			std::cout << RED << "Error: Numbers are already sorted." << RESET << std::endl;
			throw std::invalid_argument("Invalid number: already sorted");
		}

		if (_numbers.size() % 2 != 0)
		{
			stragglers = _numbers.back();
			_numbers.pop_back();
		}

		
		
		size_t PairDequeSize = createPairDeques();
		makePairDeques(PairDeques, PairDequeSize);
		
#ifdef DEBUG
		std::cout << YELLOW << "=== STEPS 1: MAKING PairDequeS AND HANDLE STRAGGLER ===" << RESET << std::endl;
		std::cout << YELLOW << "=== STEPS 2: SORT PairDequeS ===" << RESET << std::endl;
		displayPairDeque(PairDeques);
		if (stragglers != -1)
			std::cout << "Straggler store: " << stragglers << std::endl;
		else
			std::cout << "Straggler store: " << "none" << std::endl;
		std::cout << YELLOW << "=== STEP 3: RECURSIVE PairDequeS ===" << RESET << std::endl;
		// std::cout << YELLOW << "=== STEP 3: RECURSIVE PairDequeS ===" << RESET << std::endl;
		// std::cout << YELLOW << "=== STEP 3: RECURSIVE PairDequeS ===" << RESET << std::endl;
#endif

		recursivePairDeques(PairDeques, PairDequeSize);
		if (stragglers != -1)
		{
			std::deque<int> stragglers_deque;
			stragglers_deque.push_back(stragglers);
			std::deque<int>::iterator it = std::lower_bound(_numbers.begin(), _numbers.end(), stragglers);
			_numbers.insert(it, stragglers_deque.begin(), stragglers_deque.end());
		}
		std::cout << GREEN << "After: " << RESET;
		displayNumbers();
		gettimeofday(&end, NULL);
		long microsecondes = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		std::cout << PINK << "Time to process a range of " << _numbers.size() << " with std::deque container: " << microsecondes << " µs" << RESET << std::endl;
	}

	size_t createPairDeques()
	{
		size_t size = _numbers.size();
		size_t PairDequeSize = 2;
		size_t levels = 0;

		while (PairDequeSize <= size)
		{
			for (size_t j = (PairDequeSize / 2) - 1; j + (PairDequeSize / 2) < size; j += PairDequeSize)
			{
				if (j < size && j + (PairDequeSize / 2) < size && _numbers[j] > _numbers[j + (PairDequeSize / 2)])
				for (size_t k = j - (PairDequeSize / 2) + 1; k <= j; k++)
				std::swap(_numbers[k], _numbers[k + (PairDequeSize / 2)]);
			}
			PairDequeSize *= 2;
			levels++;
		}
		if (size == 2)
			return 2;
		return PairDequeSize / 2;
	}



	void makePairDeques(std::deque<PairDeque> &PairDeques, size_t PairDequeSize)
	{
		PairDeques.clear();
		size_t size = _numbers.size();
		if (PairDequeSize < 1)
			return;

		for (size_t i = 0; i < size; i += PairDequeSize)
		{
			if (i + PairDequeSize > size)
				break;

			size_t PairDeque_number = i / PairDequeSize;
			type PairDeque_side = PairDeque_number % 2 ? B : A;
			size_t index = PairDeque_number / 2 + 1;

			std::deque<int> numbers(_numbers.begin() + i, _numbers.begin() + i + PairDequeSize);
			PairDeque new_PairDeque = {index, PairDeque_side, numbers};
			PairDeques.push_back(new_PairDeque);
		}
	}

	void recursivePairDeques(std::deque<PairDeque> &PairDeques, size_t PairDequeSize)
	{
		if (PairDequeSize < 1)
			return;

		_main.clear();
		_pend.clear();
		_rest.clear();

		size_t restIndex = _numbers.size() % PairDequeSize;
		size_t sizeNumbers = _numbers.size();
		for (int i = sizeNumbers - 1; i >= (int)(sizeNumbers - restIndex); i--)
		{
			_rest.push_back(_numbers[i]);
			_numbers.pop_back();
		}

		for (std::deque<PairDeque>::const_iterator it = PairDeques.begin(); it != PairDeques.end(); ++it)
		{
			if (it->pair_type == A)
			{
				if (it->index == 1)
					_main.push_back(*it);
				else
					_pend.push_back(*it);
			}
			else
				_main.push_back(*it);
		}

		#ifdef DEBUG
		std::cout << YELLOW << "=== STEP 4: SORT IN PEND AND MAIN ===" << RESET << std::endl;
		displayNumbers();
		displayMain();
		displayPend();
		#endif

		size_t previousLimit = 1;
		int jcb_start = 3;
		while (previousLimit < _pend.size())
		{
			size_t currentLimit = jacobstahl_numbers(jcb_start);
			size_t end = (currentLimit < _pend.size()) ? currentLimit : _pend.size();
			for (size_t i = end; i > previousLimit; i--)
			{
				size_t partner_pos = find_partner_position(_pend[i - 1]);
				insert_PairDeque(_main, _pend[i - 1], partner_pos);
			}

			_pend.erase(_pend.begin() + previousLimit, _pend.begin() + end);
			previousLimit = currentLimit;
			jcb_start++;
		}

		if (!_pend.empty())
		{
			for (std::deque<PairDeque>::const_iterator it = _pend.begin(); it != _pend.end(); ++it)
			{
				size_t partner_pos = find_partner_position(*it);
				insert_PairDeque(_main, *it, partner_pos);
			}
		}
		
		_pend.clear();
		_numbers.clear();
		#ifdef DEBUG
			std::cout << YELLOW << "=== STEP 5: SORT IN MAIN ===" << RESET << std::endl;
			displayMain();
			displayPend();
			displayRest();
		#endif

		for (std::deque<PairDeque>::const_iterator it = _main.begin(); it != _main.end(); ++it)
			for (std::deque<int>::const_iterator vec_it = it->pairDeque.begin(); vec_it != it->pairDeque.end(); ++vec_it)
				_numbers.push_back(*vec_it);

		for (std::deque<int>::reverse_iterator it = _rest.rbegin(); it != _rest.rend(); ++it)
			_numbers.push_back(*it);
		

		if (PairDequeSize > 1)
			PairDequeSize /= 2;
		else
			PairDequeSize = 0;

		makePairDeques(PairDeques, PairDequeSize);
		recursivePairDeques(PairDeques, PairDequeSize);
	}

	void insert_PairDeque(std::deque<PairDeque> &main, const PairDeque &element, int search_limit)
	{
		std::deque<PairDeque>::iterator it = std::lower_bound(main.begin(), main.begin() + search_limit,
														  element, compare_PairDeques);
		main.insert(it, element);
	}

	size_t find_partner_position(const PairDeque &pend_element)
	{
		for (size_t i = 0; i < _main.size(); i++)
		{
			if (_main[i].index == pend_element.index && _main[i].pair_type == B)
				return i + 1;
		}
		return _main.size();
	}

	static bool compare_PairDeques(const PairDeque &a, const PairDeque &b)
	{
		return a.pairDeque.back() < b.pairDeque.back();
	}

	int jacobstahl_numbers(int n)
	{
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;

		int prev2 = 0, prev1 = 1;
		for (int i = 2; i <= n; i++)
		{
			int current = prev1 + 2 * prev2;
			prev2 = prev1;
			prev1 = current;
		}
		return prev1;
	}

	// ========================================================================
	// DISPLAY AND DEBUG FUNCTIONS
	// ========================================================================

	void displayNumbers() const
	{
		std::cout << YELLOW << "Display numbers: ";
		for (std::deque<int>::const_iterator it = _numbers.begin(); it != _numbers.end(); ++it)
		{
			std::cout << BLUE << *it << " ";
		}
		std::cout << RESET << std::endl;
	}

	void displayRest() const
	{
		std::cout << CYAN << "Rest numbers: ";
		if (_rest.empty())
		{
			std::cout << CYAN << "None" << RESET << std::endl;
			return;
		}
		for (std::deque<int>::const_iterator it = _rest.begin(); it != _rest.end(); ++it)
			std::cout << RESET << *it << " ";
		std::cout << RESET << std::endl;
	}

	void displayMain() const
	{
		if (_main.empty())
		{
			std::cout << CYAN << "Main numbers: None" << RESET << std::endl;
			return;
		}

		std::cout << CYAN << "Main numbers: ";
		for (std::deque<PairDeque>::const_iterator it = _main.begin(); it != _main.end(); ++it)
		{
			std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << it->index << " " << RESET;
			for (std::deque<int>::const_iterator vec_it = it->pairDeque.begin(); vec_it != it->pairDeque.end(); ++vec_it)
				std::cout << *vec_it << " ";
			if (it != _main.end() - 1)
				std::cout << YELLOW << " | ";
			std::cout << RESET;
		}
		std::cout << std::endl;
	}

	void displayPend() const
	{
		if (_pend.empty())
		{
			std::cout << CYAN << "Pend numbers: None" << RESET << std::endl;
			return;
		}
		std::cout << CYAN << "Pend numbers: ";
		for (std::deque<PairDeque>::const_iterator it = _pend.begin(); it != _pend.end(); ++it)
		{
			if (it != _pend.begin())
				std::cout << YELLOW << " | " << RESET;
			std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << it->index << " " << RESET;
			for (std::deque<int>::const_iterator vec_it = it->pairDeque.begin(); vec_it != it->pairDeque.end(); ++vec_it)
				std::cout << *vec_it << " ";
			std::cout << RESET;
		}
		std::cout << std::endl;
	}

	void displayPairDeque(const std::deque<PairDeque> &PairDeques) const
	{
		std::deque<PairDeque>::const_iterator it = PairDeques.begin();
		for (; it != PairDeques.end(); ++it)
		{
			if (it != PairDeques.begin())
				std::cout << YELLOW << " | " << RESET;
			std::cout << MAGENTA << (it->pair_type == A ? "A" : "B") << it->index << " " << RESET;
			for (std::deque<int>::const_iterator vec_it = it->pairDeque.begin(); vec_it != it->pairDeque.end(); ++vec_it)
				std::cout << *vec_it << " ";
			std::cout << RESET;
		}
		std::cout << std::endl;
	}

	std::deque<int> getNumbers() const
	{
		return _numbers;
	}
};

#endif