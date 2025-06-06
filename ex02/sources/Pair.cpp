/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:17:01 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/06 17:30:10 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Pair.hpp"

Pair::Pair(int first, int second): _pairMax(NULL), _pairMin(NULL)
{
	if (first > second)
	{
		this->_intMax = first;
		this->_intMin = second;
	}
	else
	{
		this->_intMax = second;
		this->_intMin = first;
	}
}

Pair::Pair(Pair *first, Pair *second): _intMin(-1)
{
	if (first->getIntMax() > second->getIntMax())
	{
		this->_intMax = first->getIntMax();
		this->_pairMax = first;
		this->_pairMin = second;
	}
	else
	{
		this->_intMax = second->getIntMax();
		this->_pairMax = second;
		this->_pairMin = first;
	}
}

Pair::~Pair() { }


Pair*	Pair::deepCopy() const
{
	return new Pair(*this);
}


int	Pair::getIntMax() const
{
	return (this->_intMax);
}

int	Pair::getIntMin() const
{
	return (this->_intMin);
}

Pair	*Pair::getPairMax() const
{
	return (this->_pairMax);
}

Pair	*Pair::getPairMin() const
{
	return (this->_pairMin);
}


// int	Pair::maxIntPair(Pair *pair) const
// {
// 	if (pair->_intMax > 0)
// 		return (pair->_intMax);
// 	return (this->maxIntPair(pair->getPairMax()));
// }
