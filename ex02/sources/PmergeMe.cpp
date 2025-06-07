/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:42:20 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/07 14:37:43 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"


/* ======================================== CONSTRUCTOR AND DESTRUCTOR ======================================== */


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
	std::vector<Pair*>	pairs = makePairsVec(this->_vecInput);

	std::vector<Pair*>	sortedPairsOfPairs = recursivityPairingSortVec(pairs);
	std::vector<Pair*>	sortedPairs = insertSortVec(sortedPairsOfPairs);
	std::vector<int>	preSortedInt = unpairToIntVec(sortedPairs);

	if (this->_vecInput.size() % 2 != 0)
		preSortedInt.push_back(this->_vecInput[this->_vecInput.size() - 1]);

	std::vector<int>	finalVec = insertSortVec(preSortedInt);
	
	freePairsVec(pairs);
	freePairsVec(sortedPairsOfPairs);
	freePairsVec(sortedPairs);

	return (finalVec);
}


/* ======================================== FORD-JOHNSON LIST ======================================== */


std::list<Pair*>::const_iterator	PmergeMe::getElementList(std::list<Pair*> list, size_t index)
{
	if (index >= list.size())
	{
		std::list<Pair*>::const_iterator it = list.end();
		return (it);
	}

	std::list<Pair*>::const_iterator it = list.begin();
	std::advance(it, index);

	return (it);
}

std::list<int>::const_iterator	PmergeMe::getElementList(std::list<int> list, size_t index)
{
	if (index >= list.size())
	{
		std::list<int>::const_iterator it = list.end();
		return (it);
	}

	std::list<int>::const_iterator it = list.begin();
	std::advance(it, index);

	return (it);
}

void	PmergeMe::insertAtIndexList(std::list<Pair*> &list, Pair *pair, size_t index)
{
	std::list<Pair*>::iterator it = list.begin();
	std::advance(it, index);

	list.insert(it, pair);
}

void	PmergeMe::insertAtIndexList(std::list<int> &list, int integer, size_t index)
{
	std::list<int>::iterator it = list.begin();
	std::advance(it, index);

	list.insert(it, integer);
}

void	PmergeMe::freePairsList(std::list<Pair*> &list)
{
	for (std::list<Pair*>::iterator it = list.begin(); it != list.end(); ++it)
		delete *it;

	list.clear();
}

std::list<Pair*>	PmergeMe::makePairsList(const std::list<Pair*> &list)
{
	std::list<Pair*>					pairs;
	std::list<Pair*>::const_iterator	it1 = list.begin();
	std::list<Pair*>::const_iterator	it2 = list.begin();

	++it2;
	while (it1 != list.end() && it2 != list.end())
	{
		Pair *tmp = new Pair(*it1, *it2);
		pairs.push_back(tmp);
		++it1;
		++it1;
		++it2;
		++it2;
	}

	return (pairs);
}

std::list<Pair*>	PmergeMe::makePairsList(const std::list<int> &list)
{
	std::list<Pair*>					pairs;
	std::list<int>::const_iterator	it1 = list.begin();
	std::list<int>::const_iterator	it2 = list.begin();

	++it2;
	while (it2 != list.end())
	{
		Pair *tmp = new Pair(*it1, *it2);
		pairs.push_back(tmp);
		++it1;
		++it1;
		++it2;
		++it2;
	}

	return (pairs);
}

std::list<int>	PmergeMe::unpairToIntList(std::list<Pair*> pairs)
{
	std::list<int>	list;

	for (std::list<Pair*>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		list.push_back((*it)->getIntMin());
		list.push_back((*it)->getIntMax());
	}

	return (list);
}

std::list<Pair*>	PmergeMe::unpairToPairList(std::list<Pair*> pairs)
{
	std::list<Pair*>	list;

	for (std::list<Pair*>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		list.push_back((*it)->getPairMin()->deepCopy());
		list.push_back((*it)->getPairMax()->deepCopy());
	}

	return (list);
}

size_t	PmergeMe::findIndexList(std::list<Pair*> list, int insert, int min, int max)
{
	int	actualIndex = 0;
	
	while (insert != (*getElementList(list, actualIndex))->getIntMax() && min < max)
	{
		actualIndex = (min + max) / 2;
		
		if (insert > (*getElementList(list, actualIndex))->getIntMax())
			min = actualIndex + 1;
		else
			max = actualIndex;
	}

	if (min >= max)
	return (min);

	return (actualIndex);
}

size_t	PmergeMe::findIndexList(std::list<int> list, int insert, int min, int max)
{
	int	actualIndex = 0;

	while (insert != (*getElementList(list, actualIndex)) && min < max)
	{
		actualIndex = (min + max) / 2;
		
		if (insert > (*getElementList(list, actualIndex)))
			min = actualIndex + 1;
		else
			max = actualIndex;
	}

	if (min >= max)
	return (min);

	return (actualIndex);
}

std::list<Pair*>	PmergeMe::insertSortList(std::list<Pair*> &list)
{
	std::list<Pair*>	listSorted;
	int					index = 0;
	
	listSorted.push_back((*getElementList(list, 0))->deepCopy());
	listSorted.push_back((*getElementList(list, 1))->deepCopy());
	
	for (int k = 2; listSorted.size() < list.size(); ++k)
	{
		unsigned long	t = jacobsthal(k);
		unsigned long	tPrev = jacobsthal(k - 1);
		if (t > list.size() - 1)
		t = list.size() - 1;
		while (t > tPrev)
		{
			int	max = 1 << k;
			if ((size_t)max >= listSorted.size())
			max = listSorted.size();
			
			index = findIndexList(listSorted, (*getElementList(list, t))->getIntMax(), 0, max);
			insertAtIndexList(listSorted, (*getElementList(list, t))->deepCopy(), index);
			
			--t;
		}
	}
	
	return (listSorted);
}

std::list<int>		PmergeMe::insertSortList(std::list<int> &list)
{
	std::list<int>		listSorted;
	int					index = 0;
	
	listSorted.push_back((*getElementList(list, 0)));
	listSorted.push_back((*getElementList(list, 1)));
	
	for (int k = 2; listSorted.size() < list.size(); ++k)
	{
		unsigned long	t = jacobsthal(k);
		unsigned long	tPrev = jacobsthal(k - 1);
		if (t > list.size() - 1)
		t = list.size() - 1;
		while (t > tPrev)
		{
			int	max = 1 << k;
			if ((size_t)max >= listSorted.size())
			max = listSorted.size();
			
			index = findIndexList(listSorted, (*getElementList(list, t)), 0, max);
			insertAtIndexList(listSorted, (*getElementList(list, t)), index);
			
			--t;
		}
	}
	
	return (listSorted);
}

std::list<Pair*>	PmergeMe::recursivityPairingSortList(const std::list<Pair*> &previousList)
{
	std::list<Pair*>	listPaired = makePairsList(previousList);

	if (listPaired.size() == 1)
	{
		std::list<Pair*>	finalPairs;

		finalPairs.push_back((*getElementList(listPaired, 0))->getPairMin()->deepCopy());
		finalPairs.push_back((*getElementList(listPaired, 0))->getPairMax()->deepCopy());
		if (previousList.size() == 3)
			finalPairs.push_back((*getElementList(previousList, 2)));

		freePairsList(listPaired);

		return (finalPairs);
	}

	std::list<Pair*>	listPairedSorted = recursivityPairingSortList(listPaired);
	std::list<Pair*>	list = unpairToPairList(listPairedSorted);

	if (previousList.size() % 2 != 0)
		list.push_back((*getElementList(previousList, previousList.size() - 1))->deepCopy());

	std::list<Pair*>	finalList = insertSortList(list);

	freePairsList(listPaired);
	if (listPairedSorted.size() == 2 || listPairedSorted.size() == 3)
	{
		for (size_t i = 0; i < listPairedSorted.size() - (listPairedSorted.size() == 3); ++i)
			delete *getElementList(listPairedSorted, i);

		listPairedSorted.clear();
	}
	else
		freePairsList(listPairedSorted);
	freePairsList(list);

	return (finalList);
}

std::list<int>		PmergeMe::fordJohnsonSortList()
{
	std::list<Pair*>	pairs = makePairsList(this->_listInput);
	
	std::list<Pair*>	sortedPairsOfPairs = recursivityPairingSortList(pairs);
	std::list<Pair*>	sortedPairs = insertSortList(sortedPairsOfPairs);
	std::list<int>	preSortedInt = unpairToIntList(sortedPairs);
	
	if (this->_vecInput.size() % 2 != 0)
	preSortedInt.push_back(this->_vecInput[this->_vecInput.size() - 1]);
	
	std::list<int>	finalVec = insertSortList(preSortedInt);
	
	freePairsList(pairs);
	freePairsList(sortedPairsOfPairs);
	freePairsList(sortedPairs);
	
	return (finalVec);
}
