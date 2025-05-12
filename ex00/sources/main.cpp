/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:20:57 by agerbaud          #+#    #+#             */
/*   Updated: 2025/05/12 20:35:14 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (displayError("error: usage: ./btc [file.txt]", true));

	std::string	file = av[1];
	if (file.length() < 4 || file.compare(file.length() - 4, 4, ".txt"))
		return (displayError("error: usage: ./btc [file.txt]", true));

	std::map<std::string, double>	data;
	try
	{
		data = extractData(SRC_FILE);
	}
	catch (std::exception &e)
	{
		return (displayError(std::string("error: ") + e.what(), true));
	}

	displayInput(file, data);

	return (0);
}
