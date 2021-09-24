/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:30:25 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/19 15:25:16 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
 #define ALGORITHM_HPP

namespace ft
{
	/*
		equal function template
		Compares the elements in the range [first1,last1) with those in the range beginning at first2,
		and returns true if all of the elements in both ranges match.
		https://www.cplusplus.com/reference/algorithm/equal/
	*/
	template <typename InputIterator1, typename InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}
	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}
	template <class T>
	const T &	min(const T& a, const T& b)
	{
		return (!(b < a) ? a : b);
	}
	/*
		lexicographical_compare
		Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2)
		https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
	*/
	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
    		first1++;
			first2++;
		}
		return (first2 != last2);
	}
	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
    		first1++;
			first2++;
		}
		return (first2 != last2);
	}
}

#endif