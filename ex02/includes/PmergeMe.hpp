/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:36:10 by agerbaud          #+#    #+#             */
/*   Updated: 2025/05/14 14:38:03 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// LIBRARIES INCLUDES
# include <algorithm>
# include <errno.h>
# include <iostream>
# include <list>
# include <ctime>
# include <vector>

// DEFINES COLORS
# define RED	"\033[31m"
# define RESET	"\033[0m"


// SORT FUNCTIONS
std::vector<int>	fordJohnsonSort(const std::vector<int> &input);
std::list<int>		fordJohnsonSort(const std::list<int> &input);

// UTILS
bool				isPositiveInteger(char *str);
bool				fillParseInput(int ac, char **av, std::vector<int> &vecInput);