/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 18:16:16 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/19 15:00:18 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
 #define UTILITY_HPP

namespace ft
{
	/*
		pair typename template below
		This typename couples together a pair of values, which may be of different types (T1 and T2).
		The individual values can be accessed through its public members first and second.
		https://www.cplusplus.com/reference/utility/pair/
	*/
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1	first_type;
		typedef	T2	second_type;

		T1	first;
		T2	second;

		pair(void)
			: first(T1()), second(T2()) {};
		template<typename U, typename V>
		pair(const pair<U, V> & pr)
			: first(pr.first), second(pr.second) {};
		pair(const first_type & a, const second_type & b)
			: first(a), second(b) {};

		pair &	operator=(const pair & pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}
	};
	template <typename T1, typename T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template <typename T1, typename T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <typename T1, typename T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}
	template <typename T1, typename T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (!(rhs < lhs));
	}
	template <typename T1, typename T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (rhs < lhs);
	}
	template <typename T1, typename T2>
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (!(lhs < rhs));
	}
	/*
		make_pair function template below
		Constructs a pair object with its first element set to x and its second element set to y
		https://www.cplusplus.com/reference/utility/make_pair/
	*/
	template <typename T1,typename T2>
	pair<T1,T2>	make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
}

#endif