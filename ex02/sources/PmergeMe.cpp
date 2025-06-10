/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:42:20 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/10 15:32:23 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"


/* ======================================== CONSTRUCTOR AND DESTRUCTOR ======================================== */


PmergeMe::PmergeMe(int ac, char **av)
{
	// CREATE VECTOR WITH INPUT
	if (fillParseInput(ac, av, this->_vecInput))
		throw std::exception();

	// CREATE DEQUE WITH VECTOR
	for (std::vector<int>::iterator it = this->_vecInput.begin(); it != this->_vecInput.end(); ++it)
		this->_dequeInput.push_back(*it);
}

PmergeMe::~PmergeMe() { }


/* ======================================== GETTER ======================================== */


std::vector<int>	PmergeMe::getVecInput() const
{
	return (this->_vecInput);
}


/* ======================================== PARSING ======================================== */


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


/* ======================================== JACOBSTHAL ======================================== */


unsigned long	PmergeMe::jacobsthal(unsigned int k)
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


/* ======================================== FORD-JOHNSON VECTOR ======================================== */


void	PmergeMe::freePairsVec(std::vector<Pair*> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		delete vec[i];

	vec.clear();
}

std::vector<Pair*>	PmergeMe::makePairsVec(const std::vector<Pair*> &vec)
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

std::vector<Pair*>	PmergeMe::makePairsVec(const std::vector<int> &vec)
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

std::vector<int>	PmergeMe::unpairToIntVec(std::vector<Pair*> pairs)
{
	std::vector<int>	vec;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		vec.push_back(pairs[i]->getIntMin());
		vec.push_back(pairs[i]->getIntMax());
	}

	return (vec);
}

std::vector<Pair*>	PmergeMe::unpairToPairVec(std::vector<Pair*> pairs)
{
	std::vector<Pair*>	vec;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		vec.push_back(pairs[i]->getPairMin()->deepCopy());
		vec.push_back(pairs[i]->getPairMax()->deepCopy());
	}

	return (vec);
}

size_t	PmergeMe::findIndexVec(std::vector<Pair*> vec, int insert, int min, int max)
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

size_t	PmergeMe::findIndexVec(std::vector<int> vec, int insert, int min, int max)
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

std::vector<Pair*>	PmergeMe::insertSortVec(std::vector<Pair*> &vec)
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

			index = findIndexVec(vecSorted, vec[t]->getIntMax(), 0, max);
			vecSorted.insert(vecSorted.begin() + index, vec[t]->deepCopy());

			--t;
		}
	}

	return (vecSorted);
}

std::vector<int>	PmergeMe::insertSortVec(std::vector<int> &vec)
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

			index = findIndexVec(vecSorted, vec[t], 0, max);
			vecSorted.insert(vecSorted.begin() + index, vec[t]);

			--t;
		}
	}

	return (vecSorted);
}

std::vector<Pair*>	PmergeMe::recursivityPairingSortVec(const std::vector<Pair*> &previousVec)
{
	std::vector<Pair*>	vecPaired = makePairsVec(previousVec);

	if (vecPaired.size() == 1)
	{
		std::vector<Pair*>	finalPairs;

		finalPairs.push_back(vecPaired[0]->getPairMin()->deepCopy());
		finalPairs.push_back(vecPaired[0]->getPairMax()->deepCopy());
		if (previousVec.size() == 3)
			finalPairs.push_back(previousVec[2]);
		
		freePairsVec(vecPaired);

		return (finalPairs);
	}

	std::vector<Pair*>	vecPairedSorted = recursivityPairingSortVec(vecPaired);
	std::vector<Pair*>	vec = unpairToPairVec(vecPairedSorted);

	if (previousVec.size() % 2 != 0)
		vec.push_back(previousVec[previousVec.size() - 1]->deepCopy());

	std::vector<Pair*>	finalVec = insertSortVec(vec);

	freePairsVec(vecPaired);
	if (vecPairedSorted.size() == 2 || vecPairedSorted.size() == 3)
	{
		for (size_t i = 0; i < vecPairedSorted.size() - (vecPairedSorted.size() == 3); ++i)
			delete vecPairedSorted[i];

		vecPairedSorted.clear();
	}
	else
		freePairsVec(vecPairedSorted);
	freePairsVec(vec);

	return (finalVec);
}

std::vector<int>	PmergeMe::fordJohnsonSortVector()
{
	if (this->_vecInput.size() == 1)
		return (this->_vecInput);

	std::vector<Pair*>    pairs = makePairsVec(this->_vecInput);

	if (pairs.size() == 1)
	{
		std::vector<int>    preSortedInt;

		preSortedInt.push_back(pairs[0]->getIntMin());
		preSortedInt.push_back(pairs[0]->getIntMax());
		if (this->_vecInput.size() == 3)
			preSortedInt.push_back(this->_vecInput[2]);
		
		std::vector<int>    finalVec = insertSortVec(preSortedInt);

		freePairsVec(pairs);

		return (finalVec);
	}

	std::vector<Pair*>    sortedPairsOfPairs = recursivityPairingSortVec(pairs);
	std::vector<Pair*>    sortedPairs = insertSortVec(sortedPairsOfPairs);
	std::vector<int>    preSortedInt = unpairToIntVec(sortedPairs);

	if (this->_vecInput.size() % 2 != 0)
		preSortedInt.push_back(this->_vecInput[this->_vecInput.size() - 1]);

	std::vector<int>    finalVec = insertSortVec(preSortedInt);
	
	freePairsVec(pairs);
	freePairsVec(sortedPairsOfPairs);
	freePairsVec(sortedPairs);

	return (finalVec);
}


/* ======================================== FORD-JOHNSON DEQUE ======================================== */


void	PmergeMe::freePairsDeque(std::deque<Pair*> &deque)
{
	for (size_t i = 0; i < deque.size(); ++i)
		delete deque[i];

	deque.clear();
}

std::deque<Pair*>	PmergeMe::makePairsDeque(const std::deque<Pair*> &deque)
{
	std::deque<Pair*>	pairs;
	size_t				dequeSize = deque.size();
	
	for (size_t i = 0; i + 1 < dequeSize; i += 2)
	{
		Pair *tmp = new Pair(deque[i], deque[i + 1]);
		pairs.push_back(tmp);
	}

	return (pairs);
}

std::deque<Pair*>	PmergeMe::makePairsDeque(const std::deque<int> &deque)
{
	std::deque<Pair*>	pairs;
	size_t				dequeSize = deque.size();
	
	for (size_t i = 0; i + 1 < dequeSize; i += 2)
	{
		Pair *tmp = new Pair(deque[i], deque[i + 1]);
		pairs.push_back(tmp);
	}

	return (pairs);
}

std::deque<int>	PmergeMe::unpairToIntDeque(std::deque<Pair*> pairs)
{
	std::deque<int>	deque;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		deque.push_back(pairs[i]->getIntMin());
		deque.push_back(pairs[i]->getIntMax());
	}

	return (deque);
}

std::deque<Pair*>	PmergeMe::unpairToPairDeque(std::deque<Pair*> pairs)
{
	std::deque<Pair*>	deque;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		deque.push_back(pairs[i]->getPairMin()->deepCopy());
		deque.push_back(pairs[i]->getPairMax()->deepCopy());
	}

	return (deque);
}

size_t	PmergeMe::findIndexDeque(std::deque<Pair*> deque, int insert, int min, int max)
{
	int	actualIndex = 0;

	while (insert != deque[actualIndex]->getIntMax() && min < max)
	{
		actualIndex = (min + max) / 2;

		if (insert > deque[actualIndex]->getIntMax())
			min = actualIndex + 1;
		else
			max = actualIndex;
	}

	if (min >= max)
		return (min);

	return (actualIndex);
}

size_t	PmergeMe::findIndexDeque(std::deque<int> deque, int insert, int min, int max)
{
	int	actualIndex = 0;

	while (insert != deque[actualIndex] && min < max)
	{
		actualIndex = (min + max) / 2;

		if (insert > deque[actualIndex])
			min = actualIndex + 1;
		else
			max = actualIndex;
	}

	if (min >= max)
		return (min);

	return (actualIndex);
}

std::deque<Pair*>	PmergeMe::insertSortDeque(std::deque<Pair*> &deque)
{
	std::deque<Pair*>	dequeSorted;
	int					index = 0;

	dequeSorted.push_back(deque[0]->deepCopy());
	dequeSorted.push_back(deque[1]->deepCopy());

	for (int k = 2; dequeSorted.size() < deque.size(); ++k)
	{
		unsigned long	t = jacobsthal(k);
		unsigned long	tPrev = jacobsthal(k - 1);
		if (t > deque.size() - 1)
			t = deque.size() - 1;
		while (t > tPrev)
		{
			int	max = 1 << k;
			if ((size_t)max >= dequeSorted.size())
				max = dequeSorted.size();

			index = findIndexDeque(dequeSorted, deque[t]->getIntMax(), 0, max);
			dequeSorted.insert(dequeSorted.begin() + index, deque[t]->deepCopy());

			--t;
		}
	}

	return (dequeSorted);
}

std::deque<int>	PmergeMe::insertSortDeque(std::deque<int> &deque)
{
	std::deque<int>	dequeSorted;
	int					index = 0;

	dequeSorted.push_back(deque[0]);
	dequeSorted.push_back(deque[1]);

	for (int k = 2; dequeSorted.size() < deque.size(); ++k)
	{
		unsigned long	t = jacobsthal(k);
		unsigned long	tPrev = jacobsthal(k - 1);
		if (t > deque.size() - 1)
			t = deque.size() - 1;
		
		while (t > tPrev)
		{
			int	max = 1 << k;
			if ((size_t)max >= dequeSorted.size())
				max = dequeSorted.size();

			index = findIndexDeque(dequeSorted, deque[t], 0, max);
			dequeSorted.insert(dequeSorted.begin() + index, deque[t]);

			--t;
		}
	}

	return (dequeSorted);
}

std::deque<Pair*>	PmergeMe::recursivityPairingSortDeque(const std::deque<Pair*> &previousdeque)
{
	std::deque<Pair*>	dequePaired = makePairsDeque(previousdeque);

	if (dequePaired.size() == 1)
	{
		std::deque<Pair*>	finalPairs;

		finalPairs.push_back(dequePaired[0]->getPairMin()->deepCopy());
		finalPairs.push_back(dequePaired[0]->getPairMax()->deepCopy());
		if (previousdeque.size() == 3)
			finalPairs.push_back(previousdeque[2]);
		
		freePairsDeque(dequePaired);

		return (finalPairs);
	}

	std::deque<Pair*>	dequePairedSorted = recursivityPairingSortDeque(dequePaired);
	std::deque<Pair*>	deque = unpairToPairDeque(dequePairedSorted);

	if (previousdeque.size() % 2 != 0)
		deque.push_back(previousdeque[previousdeque.size() - 1]->deepCopy());

	std::deque<Pair*>	finaldeque = insertSortDeque(deque);

	freePairsDeque(dequePaired);
	if (dequePairedSorted.size() == 2 || dequePairedSorted.size() == 3)
	{
		for (size_t i = 0; i < dequePairedSorted.size() - (dequePairedSorted.size() == 3); ++i)
			delete dequePairedSorted[i];

		dequePairedSorted.clear();
	}
	else
		freePairsDeque(dequePairedSorted);
	freePairsDeque(deque);

	return (finaldeque);
}

std::deque<int>	PmergeMe::fordJohnsonSortDeque()
{
	if (this->_dequeInput.size() == 1)
		return (this->_dequeInput);

	std::deque<Pair*>    pairs = makePairsDeque(this->_dequeInput);

	if (pairs.size() == 1)
	{
		std::deque<int>    preSortedInt;

		preSortedInt.push_back(pairs[0]->getIntMin());
		preSortedInt.push_back(pairs[0]->getIntMax());
		if (this->_dequeInput.size() == 3)
			preSortedInt.push_back(this->_dequeInput[2]);
		
		std::deque<int>	finaldeque = insertSortDeque(preSortedInt);

		freePairsDeque(pairs);

		return (finaldeque);
	}

	std::deque<Pair*>    sortedPairsOfPairs = recursivityPairingSortDeque(pairs);
	std::deque<Pair*>    sortedPairs = insertSortDeque(sortedPairsOfPairs);
	std::deque<int>    preSortedInt = unpairToIntDeque(sortedPairs);

	if (this->_dequeInput.size() % 2 != 0)
		preSortedInt.push_back(this->_dequeInput[this->_dequeInput.size() - 1]);

	std::deque<int>    finaldeque = insertSortDeque(preSortedInt);
	
	freePairsDeque(pairs);
	freePairsDeque(sortedPairsOfPairs);
	freePairsDeque(sortedPairs);

	return (finaldeque);
}
