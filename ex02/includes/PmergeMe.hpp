/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:42:08 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/17 16:59:54 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// LIBRARIES INCLUDES
# include <algorithm>
# include <ctime>
# include <deque>
# include <errno.h>
# include <exception>
# include <iostream>
# include <list>
# include <vector>
# include "Pair.hpp"

// DEFINES COLORS
# define RED	"\033[31m"
# define RESET	"\033[0m"

class	PmergeMe
{
	private:
		std::vector<int>	_vecInput;
		std::deque<int>		_dequeInput;


		// CANONICAL FORM
		PmergeMe(const PmergeMe &src);
		PmergeMe	&operator=(const PmergeMe &src);

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
		
		// FORD-JOHNSON DEQUE
		void				freePairsDeque(std::deque<Pair*> &vec);
		std::deque<Pair*>	makePairsDeque(const std::deque<Pair*> &vec);
		std::deque<Pair*>	makePairsDeque(const std::deque<int> &vec);
		std::deque<Pair*>	unpairToPairDeque(std::deque<Pair*> pairs);
		std::deque<int>		unpairToIntDeque(std::deque<Pair*> pairs);
		size_t				findIndexDeque(std::deque<Pair*> vec, int insert, int min, int max);
		size_t				findIndexDeque(std::deque<int> vec, int insert, int min, int max);
		std::deque<Pair*>	insertSortDeque(std::deque<Pair*> &vec);
		std::deque<int>		insertSortDeque(std::deque<int> &vec);
		std::deque<Pair*>	recursivityPairingSortDeque(const std::deque<Pair*> &previousVec);
		
		public:
		// CONSTRUCTOR AND DESTRUCTOR
		PmergeMe(int ac, char **av);
		~PmergeMe();
		
		// GETTER
		std::vector<int>	getVecInput() const;

		// PUBLIC MEMBER FUNCTIONS
		std::vector<int>	fordJohnsonSortVector();
		std::deque<int>		fordJohnsonSortDeque();
};

#endif
