/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:42:08 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/07 13:27:34 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// LIBRARIES INCLUDES
# include <algorithm>
# include <ctime>
# include <errno.h>
# include <exception>
# include <iostream>
# include <list>
# include <vector>
# include "Pair.hpp"

// DEFINES COLORS
# define RED	"\033[31m"
# define RESET	"\033[0m"

class PmergeMe
{
	private:
		std::vector<int>	_vecInput;
		std::list<int>		_listInput;


		// PARSING
		bool				isPositiveInteger(char *str);
		bool				fillParseInput(int ac, char **av, std::vector<int> &vecInput);

		// JACOBSTHAL
		unsigned long		jacobsthal(unsigned int k);

		// FORD-JOHNSON VECTOR
		void				freePairsVec(std::vector<Pair*> &vec);
		std::vector<Pair*>	makePairsVec(const std::vector<Pair*> &vec);
		std::vector<Pair*>	makePairsVec(const std::vector<int> &vec);
		std::vector<Pair*>	unpairToPairVec(std::vector<Pair*> pairs);
		std::vector<int>	unpairToIntVec(std::vector<Pair*> pairs);
		size_t				findIndexVec(std::vector<Pair*> vec, int insert, int min, int max);
		size_t				findIndexVec(std::vector<int> vec, int insert, int min, int max);
		std::vector<Pair*>	insertSortVec(std::vector<Pair*> &vec);
		std::vector<int>	insertSortVec(std::vector<int> &vec);
		std::vector<Pair*>	recursivityPairingSortVec(const std::vector<Pair*> &previousVec);

		// FORD-JOHNSON LIST
		std::list<Pair*>::const_iterator	getElementList(std::list<Pair*> list, size_t index);
		std::list<int>::const_iterator		getElementList(std::list<int> list, size_t index);
		void								insertAtIndexList(std::list<Pair*> &list, Pair *pair, size_t index);
		void								insertAtIndexList(std::list<int> &list, int integer, size_t index);
		void								freePairsList(std::list<Pair*> &list);
		std::list<Pair*>					makePairsList(const std::list<Pair*> &list);
		std::list<Pair*>					makePairsList(const std::list<int> &list);
		std::list<Pair*>					unpairToPairList(std::list<Pair*> pairs);
		std::list<int>						unpairToIntList(std::list<Pair*> pairs);
		size_t								findIndexList(std::list<Pair*> list, int insert, int min, int max);
		size_t								findIndexList(std::list<int> list, int insert, int min, int max);
		std::list<Pair*>					insertSortList(std::list<Pair*> &list);
		std::list<int>						insertSortList(std::list<int> &list);
		std::list<Pair*>					recursivityPairingSortList(const std::list<Pair*> &previousList);


	public:
		// CONSTRUCTOR AND DESTRUCTOR
		PmergeMe(int ac, char **av);
		~PmergeMe();

		// GETTER
		std::vector<int>	getVecInput() const;

		// PUBLIC MEMBER FUNCTIONS
		std::vector<int>	fordJohnsonSortVector();
		std::list<int>		fordJohnsonSortList();
};

#endif