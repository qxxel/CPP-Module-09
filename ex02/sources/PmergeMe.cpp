/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:42:20 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/06 18:16:30 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(int ac, char **av)
{
	// CREATE VECTOR WITH INPUT
	if (fillParseInput(ac, av, this->_vecInput))
		throw std::exception();

	// CREATE LIST WITH VECTOR
	for (std::vector<int>::iterator it = this->_vecInput.begin(); it != this->_vecInput.end(); ++it)
		this->_listInput.push_back(*it);
}

PmergeMe::~PmergeMe() { }


void	PmergeMe::freePairs(std::vector<Pair*> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		delete vec[i];

	vec.clear();
}

std::vector<int>	PmergeMe::getVecInput() const
{
	return (this->_vecInput);
}


// CHECK IF THE STRING IS FULL OF VALID DIGIT
bool	PmergeMe::isPositiveInteger(char *str)
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
bool	PmergeMe::fillParseInput(int ac, char **av, std::vector<int> &vecInput)
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

std::vector<Pair*>	makePairs(const std::vector<Pair*> &vec)
{
	std::vector<Pair*>	pairs;
	size_t				vecSize = vec.size();
	
	for (size_t i = 0; i + 1 < vecSize; i += 2)
	{
		Pair *tmp = new Pair(vec[i], vec[i + 1]);
		pairs.push_back(tmp);
	}

	return (pairs);
}

std::vector<Pair*>	makePairs(const std::vector<int> &vec)
{
	std::vector<Pair*>	pairs;
	size_t				vecSize = vec.size();
	
	for (size_t i = 0; i + 1 < vecSize; i += 2)
	{
		Pair *tmp = new Pair(vec[i], vec[i + 1]);
		pairs.push_back(tmp);
	}

	return (pairs);
}

std::vector<int>	unpairToInt(std::vector<Pair*> pairs)
{
	std::vector<int>	vec;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		vec.push_back(pairs[i]->getIntMin());
		vec.push_back(pairs[i]->getIntMax());
	}

	return (vec);
}

std::vector<Pair*>	unpairToPair(std::vector<Pair*> pairs)
{
	std::vector<Pair*>	vec;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		vec.push_back(pairs[i]->getPairMin()->deepCopy());
		vec.push_back(pairs[i]->getPairMax()->deepCopy());
	}

	return (vec);
}

unsigned long jacobsthal(unsigned int k)
{
	if (k > 49)
		return (0);

	k += 1;

	if (k == 1)
		return (1);

	unsigned long	prev2 = 0;
	unsigned long	prev1 = 1;
	unsigned long	current = 0;

	for (unsigned int i = 2; i <= k; ++i)
	{
		current = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = current;
	}

	return (current);
}

size_t	PmergeMe::findIndex(std::vector<Pair*> vec, int insert, int min, int max)
{
	int	actualIndex = 0;

	while (insert != vec[actualIndex]->getIntMax() && min < max)
	{
		actualIndex = (min + max) / 2;

		if (insert > vec[actualIndex]->getIntMax())
			min = actualIndex + 1;
		else
			max = actualIndex;
	}

	if (min >= max)
		return (min);

	return (actualIndex);
}

size_t	PmergeMe::findIndex(std::vector<int> vec, int insert, int min, int max)
{
	int	actualIndex = 0;

	while (insert != vec[actualIndex] && min < max)
	{
		actualIndex = (min + max) / 2;

		if (insert > vec[actualIndex])
			min = actualIndex + 1;
		else
			max = actualIndex;
	}

	if (min >= max)
		return (min);

	return (actualIndex);
}

std::vector<Pair*>	PmergeMe::insertSort(std::vector<Pair*> &vec)
{
	std::vector<Pair*>	vecSorted;
	int					index = 0;

	vecSorted.push_back(vec[0]->deepCopy());
	vecSorted.push_back(vec[1]->deepCopy());

	for (int k = 2; vecSorted.size() < vec.size(); ++k)
	{
		unsigned long	t = jacobsthal(k);
		unsigned long	tPrev = jacobsthal(k - 1);
		if (t > vec.size() - 1)
			t = vec.size() - 1;
		while (t > tPrev)
		{
			int	max = 1 << k;
			if ((size_t)max >= vecSorted.size())
				max = vecSorted.size();

			index = findIndex(vecSorted, vec[t]->getIntMax(), 0, max);
			vecSorted.insert(vecSorted.begin() + index, vec[t]->deepCopy());

			--t;
		}
	}

	return (vecSorted);
}

std::vector<int>	PmergeMe::insertSort(std::vector<int> &vec)
{
	std::vector<int>	vecSorted;
	int					index = 0;

	vecSorted.push_back(vec[0]);
	vecSorted.push_back(vec[1]);

	for (int k = 2; vecSorted.size() < vec.size(); ++k)
	{
		unsigned long	t = jacobsthal(k);
		unsigned long	tPrev = jacobsthal(k - 1);
		if (t > vec.size() - 1)
			t = vec.size() - 1;
		
		while (t > tPrev)
		{
			int	max = 1 << k;
			if ((size_t)max >= vecSorted.size())
				max = vecSorted.size();

			index = findIndex(vecSorted, vec[t], 0, max);
			vecSorted.insert(vecSorted.begin() + index, vec[t]);

			--t;
		}
	}

	return (vecSorted);
}

std::vector<Pair*>	PmergeMe::recursivityPairingSort(const std::vector<Pair*> &previousVec)
{
	std::vector<Pair*>	vecPaired = makePairs(previousVec);

	if (vecPaired.size() == 1)
	{
		std::vector<Pair*>	finalPairs;

		finalPairs.push_back(vecPaired[0]->getPairMin()->deepCopy());
		finalPairs.push_back(vecPaired[0]->getPairMax()->deepCopy());
		if (previousVec.size() == 3)
			finalPairs.push_back(previousVec[2]);
		
		freePairs(vecPaired);

		return (finalPairs);
	}

	std::vector<Pair*>	vecPairedSorted = recursivityPairingSort(vecPaired);
	std::vector<Pair*>	vec = unpairToPair(vecPairedSorted);

	if (previousVec.size() % 2 != 0)
		vec.push_back(previousVec[previousVec.size() - 1]->deepCopy());

	std::vector<Pair*>	finalVec = insertSort(vec);

	freePairs(vecPaired);
	if (vecPairedSorted.size() == 2 || vecPairedSorted.size() == 3)
	{
		for (size_t i = 0; i < vecPairedSorted.size() - (vecPairedSorted.size() == 3); ++i)
			delete vecPairedSorted[i];

		vecPairedSorted.clear();
	}
	else
		freePairs(vecPairedSorted);
	freePairs(vec);

	return (finalVec);
}

std::vector<int>	PmergeMe::fordJohnsonSortVector()
{
	std::vector<Pair*>	pairs = makePairs(this->_vecInput);

	std::vector<Pair*>	sortedPairsOfPairs = recursivityPairingSort(pairs);
	std::vector<Pair*>	sortedPairs = insertSort(sortedPairsOfPairs);
	std::vector<int>	preSortedInt = unpairToInt(sortedPairs);

	if (this->_vecInput.size() % 2 != 0)
		preSortedInt.push_back(this->_vecInput[this->_vecInput.size() - 1]);

	std::vector<int>	finalVec = insertSort(preSortedInt);
	
	freePairs(pairs);
	freePairs(sortedPairsOfPairs);
	freePairs(sortedPairs);

	return (finalVec);
}

// std::list<int>		PmergeMe::fordJohnsonSortList()
// {
	
// }
