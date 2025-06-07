/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:42:26 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/07 13:22:26 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

int	main(int ac, char **av)
{
	// IF THERE IS NO ARGS
	if (ac < 2)
	{
		std::cerr << RED << "Usage: ./PmergeMe <positive integer list>" << RESET << std::endl;
		return (1);
	}

	PmergeMe	*pmergeme = NULL;
	// TRY TO CREATE VECTOR AND LIST WITH INPUT
	try
	{
		pmergeme = new PmergeMe(ac, av);
		
		std::clock_t vecStart = std::clock();
		std::vector<int> vecResult = pmergeme->fordJohnsonSortVector();
		std::clock_t vecEnd = std::clock();
		double	vecDurationUs = 1000000.0 * (vecEnd - vecStart) / CLOCKS_PER_SEC;
		
		
		// SORT WITH LIST AND GET TIME
		std::clock_t listStart = std::clock();
		std::list<int> listResult = pmergeme->fordJohnsonSortList();
		std::clock_t listEnd = std::clock();
		double	listDurationUs = 1000000.0 * (listEnd - listStart) / CLOCKS_PER_SEC;


		// SHOW RESULTS
		std::cout << "Before:\t";
		for (size_t i = 0; i < pmergeme->getVecInput().size(); ++i)
		{
			if (i != 0)
				std::cout << " ";
			std::cout << pmergeme->getVecInput()[i];
		}
		std::cout << std::endl;

		std::cout << "After:\t";
		for (size_t i = 0; i < vecResult.size(); ++i)
		{
			if (i != 0)
				std::cout << " ";
			std::cout << vecResult[i];
		}
		std::cout << std::endl;

		std::cout << "Time to process a range of " << pmergeme->getVecInput().size() << " elements with std::vector : " << vecDurationUs << " us" << std::endl;
		std::cout << "Time to process a range of " << pmergeme->getVecInput().size() << " elements with std::list : " << listDurationUs << " us" << std::endl;

		delete pmergeme;
	}
	catch(const std::exception &)
	{
		return (1);
	}


	return (0);
}
