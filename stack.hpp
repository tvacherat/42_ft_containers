/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:38:29 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/07 13:20:59 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
 #define STACK_HPP

#include "vector.hpp"

namespace ft
{
	/*
		stack class definition below
		LIFO stack
		https://www.cplusplus.com/reference/stack/stack/
	*/ 
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
		protected:
			Container	m_c;

		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef unsigned int	size_t;

			explicit stack(const container_type & ctnr = container_type()): m_c(ctnr) {};
			~stack(void) {};

			bool	empty() const
			{
				return (m_c.empty());
			}
			void	pop(void)
			{
				m_c.pop_back();
			}
			void	push(const value_type & val)
			{
				m_c.push_back(val);
			}
			size_t	size(void) const
			{
				return (m_c.size());
			}
			value_type &	top(void)
			{
				return (m_c.back());
			}
			const value_type &	top(void) const
			{
				return (m_c.back());
			}
	
		template <typename Type, typename Cont>
		friend bool operator==(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator!=(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator<(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator<=(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator>(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
		template <typename Type, typename Cont>
		friend bool operator>=(const stack<Type, Cont> & lhs, const stack<Type, Cont> & rhs);
	};
	/*
		Stack's relationnal operators below
		https://www.cplusplus.com/reference/stack/stack/operators/
	*/
	template <typename T, typename Container>
	bool operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return (lhs.m_c == rhs.m_c);
	}
	template <typename T, typename Container>
	bool operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return (lhs.m_c != rhs.m_c);
	}
	template <typename T, typename Container>
	bool operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return (lhs.m_c < rhs.m_c);
	}
	template <typename T, typename Container>
	bool operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return (lhs.m_c <= rhs.m_c);
	}
	template <typename T, typename Container>
	bool operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return (lhs.m_c > rhs.m_c);
	}
	template <typename T, typename Container>
	bool operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
	{
		return (lhs.m_c >= rhs.m_c);
	}
}

#endif