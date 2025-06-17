/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:59:15 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/17 16:50:04 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

// DISPLAY
bool	displayError(std::string text, bool returnValue)
{
	std::cerr << RED << text << RESET << std::endl;
	return (returnValue);
}

void	displayValue(std::map<std::string, double> data, std::string date, double value)
{
	std::map<std::string, double>::iterator	it = data.find(date);
	if (it == data.end())
	{
		it = data.lower_bound(date);
		if (it == data.begin())
		{
			displayError("Error: bitcoin was not available at this date => " + date, false);
			return ;
		}
		--it;
	}

    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}


// PARSE
static bool	isLeapYear(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

static bool	isValidDate(std::string line)
{
	std::time_t t = std::time(0);
	std::tm* 	now = std::localtime(&t);
	int 		nowYear = now->tm_year + 1900;
	int 		nowMonth = now->tm_mon + 1;
	int 		nowDay = now->tm_mday;

	int	year = 0;
	int	month = 0;
	int	day = 0;
	int	charsConsumed = 0;
	int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

	std::size_t pos = line.find('|');
	if (sscanf(line.substr(0,pos).c_str(), "%d-%d-%d %n", &year, &month, &day, &charsConsumed) != 3 || (int)line.substr(0,pos).length() > charsConsumed)
		return (displayError("Error: wrong format => " + line, false));

	if (year < 2000 || nowYear < year || month < 1 || 12 < month || day < 1 || 31 < day)
		return (displayError("Error: bad input => " + line.substr(0, pos), false));

	if (year == nowYear)
	{
		if (month > nowMonth)
			return (displayError("Error: bad input => " + line.substr(0, pos), false));
		if (month == nowMonth && day > nowDay)
			return (displayError("Error: bad input => " + line.substr(0, pos), false));
	}

	if (month == 2 && isLeapYear(year))
	{
		if (day > 29)
			return (displayError("Error: bad input => " + line.substr(0, pos), false));
	}

	else if (day > daysInMonth[month - 1])
		return (displayError("Error: bad input => " + line.substr(0, pos), false));
	
	return (true);
}

void	parseInput(std::string line, std::map<std::string, double> data)
{
	if (line.empty())
	{
		displayError("Error: empty line.", false);
		return ;
	}

	if (line.length() >= 10 && isValidDate(line))
	{
		std::size_t pos = line.find('|');
		std::string date = line.substr(0, pos);
		double		value = 0;
		int			charsConsumed = 0;

		if (sscanf(line.c_str(), "%*s | %lf %n", &value, &charsConsumed) != 1 || (int)line.length() - (line[line.size() - 1] == '\n') > charsConsumed)
			displayError("Error: wrong format => " + line, false);

		else if (value < 0)
			displayError("Error: not a positive number.", false);
			
		else if (1000 < value)
			displayError("Error: too large a number.", false);
			
		else
			displayValue(data, date, value);
	}

	if (line.length() < 10)
		displayError("Error: wrong format => " + line, false);
}


// EXTRACT
std::map<std::string, double>	extractData(std::string fileName)
{
	std::ifstream	file(fileName.c_str());

	if (!file)
		throw CantFindData();

	std::map<std::string, double>	data;
	std::string						line;
	std::string						date;
	double							exRate;
	
	if (std::getline(file, line))
	{
		while (std::getline(file, line))
		{
			char	buf[64];

			if (sscanf(line.c_str(), "%63[^,],%lf", buf, &exRate) != 2)
				throw SscanfFailed();

			date = buf;
			data.insert(std::make_pair(date, exRate));
		}
	}

	file.close();
	return (data);
}

void	displayInput(std::string fileName, std::map<std::string, double> data)
{
	std::ifstream	file(fileName.c_str());

	if (!file)
		throw CantFindFile();

	std::string	line;

	if (std::getline(file, line))
	{
		if (line != "date | value")
			parseInput(line, data);

		while (std::getline(file, line))
			parseInput(line, data);
	}
	else
		displayError("Error: file is empty.", false);

	file.close();
}
