/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:42:08 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/05 23:19:52 by agerbaud         ###   ########.fr       */
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

		void				freePairs(std::vector<Pair*> &vec);
		bool				isPositiveInteger(char *str);
		bool				fillParseInput(int ac, char **av, std::vector<int> &vecInput);
		std::vector<Pair*>	recursivityPairingSort(const std::vector<Pair*> &previousVec);
		std::vector<int>	insertSort(std::vector<int> &vec);
		std::vector<Pair*>	insertSort(std::vector<Pair*> &vec);
		size_t				findIndex(std::vector<int> vec, int insert, int min, int max);
		size_t				findIndex(std::vector<Pair*> vec, int insert, int min, int max);

	public:
		PmergeMe(int ac, char **av);
		~PmergeMe();

		std::vector<int>	getVecInput() const;

		std::vector<int>	fordJohnsonSortVector();
		std::list<int>		fordJohnsonSortList();

		// class NotValidPositiveInteger: public std::exception
		// {
		// 	public:
		// 		const char* what() const throw() { return ("an element isn't a valid positive integer"); }
		// };
};

#endif