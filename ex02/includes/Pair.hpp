/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agerbaud <agerbaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:07:17 by agerbaud          #+#    #+#             */
/*   Updated: 2025/06/24 12:53:24 by agerbaud         ###   ########.fr       */
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
		Pair	*_pairMax;
		Pair	*_pairMin;


		// CANONICAL FORM
		Pair(const Pair &src);
		Pair	&operator=(const Pair &src);
		
	public:
		// CONSTRUCTORS AND DESTRUCTOR
		Pair(int first, int second);
		Pair(Pair *first, Pair *second);
		~Pair();
		
		// GETTERS
		int		getIntMax() const;
		int		getIntMin() const;
		Pair	*getPairMax() const;
		Pair	*getPairMin() const;
		
		// DEEP COPY
		Pair	*deepCopy() const;
};

#endif
