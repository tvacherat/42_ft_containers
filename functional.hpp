/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:28:05 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/16 16:32:04 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONAL_HPP
 #define FUNCTIONAL_HPP

namespace ft
{
	/*
		Functionnal struct definition below
		This is a base class for standard binary function objects.
		https://www.cplusplus.com/reference/functional/binary_function/?kw=binary_function
	*/
	template <typename Arg1, typename Arg2, typename Result>
  	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};
	/*
		Less struct definition below
		Binary function object class whose call returns whether the its first argument compares less than the second (as returned by operator <).
	*/
	template <class T>
	struct less : public binary_function<T, T, bool>
	{
		bool operator() (const T& x, const T& y) const
		{
			return (x < y);
		}
	};
}

#endif