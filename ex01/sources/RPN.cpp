/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:37:28 by agerbaud          #+#    #+#             */
/*   Updated: 2025/04/08 18:33:40 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int	calculate(std::string input)
{
	std::stack<double> stack;

	for (size_t i = 0; i < input.size(); i++)
	{
		char	c = input[i];
		if (c == ' ') { }
		else if (isdigit(c))
		{
			int	number = c - '0';
			stack.push(number);
		}
		else if (c == '+' && stack.size() >= 2)
		{
			double	a = stack.top();
			stack.pop();
			double	b = stack.top();
			stack.pop();
			stack.push(b + a);
		}
		else if (c == '-' && stack.size() >= 2)
		{
			double	a = stack.top();
			stack.pop();
			double	b = stack.top();
			stack.pop();
			stack.push(b - a);
		}
		else if (c == '*' && stack.size() >= 2)
		{
			double	a = stack.top();
			stack.pop();
			double	b = stack.top();
			stack.pop();
			stack.push(b * a);
		}
		else if (c == '/' && stack.size() >= 2)
		{
			double	a = stack.top();
			stack.pop();
			double	b = stack.top();
			stack.pop();
			if (a == 0)
			{
				std::cerr << RED << "Error: division by 0" << RESET << std::endl;
				return (1);
			}
			else
				stack.push(b / a);
		}
		else
		{
			std::cerr << RED << "Error: bad input" << RESET << std::endl;
			return (1);
		}
	}
	if (stack.size() != 1)
	{
		std::cerr << RED << "Error: bad input" << RESET << std::endl;
		return (1);
	}
	std::cout << "Result: " << stack.top() << std::endl;
	return (0);
}
