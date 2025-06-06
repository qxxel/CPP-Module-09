/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:07:17 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/05 23:30:46 by agerbaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <iomanip>

class Pair
{
	private:
		int		_intMax;
		int		_intMin;
		// Pair	_pairMax;
		// Pair	_pairMin;
		Pair	*_pairMax;
		Pair	*_pairMin;

	public:
		Pair(int first, int second);
		Pair(Pair *first, Pair *second);
		~Pair();

		Pair	*deepCopy() const;

		int		getIntMax() const;
		int		getIntMin() const;
		Pair	*getPairMax() const;
		Pair	*getPairMin() const;

		// int	maxIntPair(Pair *pair) const;
};

#endif
