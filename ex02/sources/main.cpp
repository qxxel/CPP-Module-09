/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:36:39 by agerbaud          #+#    #+#             */
/*   Updated: 2025/05/14 16:06:31 by agerbaud         ###   ########.fr       */
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

	
	// CREATE VECTOR WITH INPUT
	std::vector<int>	vecInput;
	if (fillParseInput(ac, av, vecInput))
		return (1);

	// SORT WITH VECTOR AND GET TIME
	std::clock_t vecStart = std::clock();
	std::vector<int> vecResult = fordJohnsonSort(vecInput);
	std::clock_t vecEnd = std::clock();
	double	vecDurationUs = 1000000.0 * (vecEnd - vecStart) / CLOCKS_PER_SEC;


	// CREATE LIST WITH INPUT
	std::list<int>	listInput;
	for (std::vector<int>::iterator it = vecInput.begin(); it != vecInput.end(); ++it)
		listInput.push_back(*it);

	// SORT WITH LIST AND GET TIME
	std::clock_t listStart = std::clock();
	std::list<int> listResult = fordJohnsonSort(listInput);
	std::clock_t listEnd = std::clock();
	double	listDurationUs = 1000000.0 * (listEnd - listStart) / CLOCKS_PER_SEC;


	// SHOW RESULTS
	std::cout << "Before:\t";
	for (size_t i = 0; i < vecInput.size(); ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << vecInput[i];
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

	std::cout << "Time to process a range of " << vecInput.size() << " elements with std::vector : " << vecDurationUs << " us" << std::endl;

	std::cout << "Time to process a range of " << listInput.size() << " elements with std::list : " << listDurationUs << " us" << std::endl;

	return (0);
}
