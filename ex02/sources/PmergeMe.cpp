/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:36:23 by agerbaud          #+#    #+#             */
/*   Updated: 2025/05/14 14:45:38 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

// CHECK IF THE STRING IS FULL OF VALID DIGIT
bool	isPositiveInteger(char *str)
{
	if (!str || !*str)
		return (false);

	for (int i = 0; str[i]; ++i)
	{
		if (!std::isdigit(str[i]))
			return (false);
	}

	return (true);
}

// FILL THE VECTOR WITH ARGS AND PARSE THEM
bool	fillParseInput(int ac, char **av, std::vector<int> &vecInput)
{
	for (int i = 1; i < ac; ++i)
	{
		if (!isPositiveInteger(av[i]))
		{
			std::cerr << "Error : \"" << av[i] << "\" isn't a valid positive integer." << std::endl;
			return (true);
		}

		errno = 0;
		double val = std::strtod(av[i], NULL);

		if (errno == ERANGE || val < 0 || 2147483647 < val)
		{
			std::cerr << "Error : \"" << av[i] << "\" isn't a valid positive integer." << std::endl;
	    	return (true);
		}

		vecInput.push_back(static_cast<int>(val));
	}
	return (false);
}

// VECTOR SORT
std::vector<int> fordJohnsonSort(const std::vector<int> &input)
{
	int	n = input.size();

	// CHECK IF THERE IS ZERO OR ONE ELEMENT
	if (n <= 1)
		return (input);

	std::vector<int>	maxList;
	std::vector<int>	minList;

	
	// SEPARATE THE VECTOR IN MAX AND MIN
	for (int i = 0; i + 1 < n; i += 2)
	{
		int	a = input[i];
		int	b = input[i + 1];

		if (a < b)
		{
			maxList.push_back(b);
			minList.push_back(a);
		}
		else
		{
			maxList.push_back(a);
			minList.push_back(b);
		}
	}

	// INSERT THE LAST INPUT IN MAXLIST IF ODD
	if (n % 2 != 0)
		maxList.push_back(input[n - 1]);

	// RECURSIVITY
	std::vector<int>	sorted = fordJohnsonSort(maxList);

	
	// INSERT MINLIST IN SORTED VECTOR
	for (size_t i = 0; i < minList.size(); ++i)
	{
		std::vector<int>::iterator	it = std::lower_bound(sorted.begin(), sorted.end(), minList[i]);
		sorted.insert(it, minList[i]);
	}

	return (sorted);
}

// LIST SORT
std::list<int> fordJohnsonSort(const std::list<int> &input)
{
	// CHECK IF THERE IS ZERO OR ONE ELEMENT
	if (input.size() <= 1)
		return (input);

	std::list<int>	maxList;
	std::list<int>	minList;

	// SEPARATE THE LIST IN MAX AND MIN
	std::list<int>::const_iterator	it = input.begin();
	while (it != input.end())
	{
		int	a = *it;

		++it;
		if (it != input.end())
		{
			int b = *it;

			if (a < b)
			{
				maxList.push_back(b);
				minList.push_back(a);
			}
			else
			{
				maxList.push_back(a);
				minList.push_back(b);
			}
		}
		else
			maxList.push_back(a);
	}

	// CHECK IF MAXLIST EQUAL TO INPUT TO AVOID SEGFAULT
	if (maxList.size() == input.size() && std::equal(maxList.begin(), maxList.end(), input.begin()))
		return (input);

	// RECURSIVITY
	std::list<int>	sorted = fordJohnsonSort(maxList);

	// INSERT MINLIST IN SORTED LIST
	std::list<int>::iterator itSort;
	for (std::list<int>::iterator itMin = minList.begin(); itMin != minList.end(); ++itMin)
	{
		itSort = sorted.begin();
		while (itSort != sorted.end() && *itSort < *itMin)
			++itSort;
		
		sorted.insert(itSort, *itMin);
	}

	return (sorted);
}
