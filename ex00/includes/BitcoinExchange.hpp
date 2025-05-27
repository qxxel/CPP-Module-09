/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:46:10 by agerbaud          #+#    #+#             */
/*   Updated: 2025/05/26 17:29:19 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <ctime>
# include <fstream>
# include <iostream>
# include <map>

# define RED	"\033[31m"
# define RESET	"\033[0m"

# define SRC_FILE	"data.csv"

struct Data {
	std::string	date;
	int			year;
	int			month;
	int			day;
	double		exRate;
};

struct Input {
	std::string	line;
	std::string	date;
	std::string	error;
	double		value;
};

class	CantFindFile: public std::exception
{
	public:
		const char* what() const throw()
		{
			return ("can't find the file");
		}
};

class	WrongLineInFile: public std::exception
{
	public:
		const char* what() const throw()
		{
			return ("wrong line in the file");
		}
};

class	SscanfFailed: public std::exception
{
	public:
		const char* what() const throw()
		{
			return ("sscanf failed during data extract, wrong format in " SRC_FILE);
		}
};

// DISPLAY
bool	displayError(std::string text, bool returnValue);
void	displayInput(std::string fileName, std::map<std::string, double> data);
void	displayValue(std::map<std::string, double> data, std::string date, double value);

// PARSING
void	parseInput(std::string input);

// EXTRACT
std::map<std::string, double>	extractData(std::string fileName);
void							extract(std::map<std::string, double> &data, std::string file);

#endif
