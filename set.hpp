/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:04:45 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/20 14:48:42 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
 #define SET_HPP

#include <memory>
#include "functional.hpp"
#include "btree.hpp"
#include "utility.hpp"

namespace ft
{
	/*
		Map class definition below
		Maps are associative containers that store elements formed by a combination of a key value and a setped value, following a specific order.
		https://www.cplusplus.com/reference/set/set/
	*/
	template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T											key_type;
			typedef T											value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
	
	
		private:
			typedef	ft::btree<value_type, value_compare, allocator_type>	_tree_type;
			
			_tree_type	m_tree;

		public:	
			typedef typename _tree_type::const_iterator						iterator;
			typedef typename _tree_type::const_iterator						const_iterator;
			typedef typename _tree_type::const_reverse_iterator					reverse_iterator;
			typedef typename _tree_type::const_reverse_iterator				const_reverse_iterator;
			typedef typename _tree_type::difference_type					difference_type;
			typedef	typename _tree_type::size_type							size_type;
			
			explicit set(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: m_tree(comp, alloc) {}
			template <class InputIterator>
			set(InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: m_tree(comp, alloc)
			{
				while (first != last)
				{
					if (m_tree.find(*first) == m_tree.end())
						m_tree.insert(*first);
					first++;
				}
			}
			set(const set & src)
				: m_tree(_tree_type(src.m_tree)) {}
			~set() {}
			iterator	begin()
			{
				return (m_tree.begin());
			}
			const_iterator	begin() const
			{
				return (m_tree.begin());
			}
			iterator	end()
			{
				return (m_tree.end());
			}
			const_iterator end() const
			{
				return (m_tree.end());
			}
			reverse_iterator rbegin()
			{
				return (m_tree.rbegin());
			}
			const_reverse_iterator rbegin() const
			{
				return (m_tree.rbegin());
			}
			reverse_iterator rend()
			{
				return (m_tree.rend());
			}
			const_reverse_iterator rend() const
			{
				return (m_tree.rend());
			}
			void	clear()
			{
				m_tree.clear();
			}
			size_type size() const
			{
				return (m_tree.size());
			}
			size_type	count(const value_type & k) const
			{
				return (m_tree.find(k) != m_tree.end() ? 1 : 0);
			}
			bool	empty() const
			{
				return (m_tree.empty());
			}
			ft::pair<iterator, iterator>	equal_range(const value_type & k) const
			{
				return (m_tree.equal_range(k));
			}
			iterator lower_bound(const value_type & k) const
			{
				return (m_tree.lower_bound(k));
			}
			iterator upper_bound(const value_type & k) const
			{
				return (m_tree.upper_bound(k));
			}
			void	erase(iterator position)
			{
				value_type	val = *position;

				m_tree.erase(val);
			}
			size_type	erase(const value_type & k)
			{
				return (m_tree.erase(k));
			}
			void	erase(iterator first, iterator last)
			{
				value_type	val;

				while (first != last)
				{
					val = *first;
					first++;
					m_tree.erase(val);
				}
			}
			iterator find(const value_type & k) const
			{
				return (m_tree.find(k));
			}
			allocator_type	get_allocator() const
			{
				return (m_tree.get_allocator());
			}
			ft::pair<iterator, bool>	insert(const value_type & val)
			{
				iterator	it = m_tree.find(val);

				if (it == m_tree.end())
					return (ft::make_pair(m_tree.insert(val), true));
				else
					return (ft::make_pair(it, false));
			}
			iterator insert(iterator position, const value_type & val)
			{
				(void)position;
				iterator	it = m_tree.find(val);

				return (it == m_tree.end() ? m_tree.insert(val) : it);
			}
			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					if (m_tree.find(*first) == m_tree.end())
						m_tree.insert(*first);
					first++;
				}
			}
			key_compare	key_comp() const
			{
				return (m_tree.get_comparator());
			}
			value_compare value_comp() const
			{
				return (m_tree.get_comparator());
			}
			size_type max_size() const
			{
				return (m_tree.max_size());
			}
			set &	operator=(const set & x)
			{
				if (this != &x)
					m_tree = x.m_tree;
				return (*this);
			}
			void	swap(set & x)
			{
				m_tree.swap(x.m_tree);
			}
	};
	template<typename T, typename Compare, typename Alloc>
	bool	operator==(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		else
			return (false);
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator!=(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator<(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator<=(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator>(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (rhs < lhs);
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator>=(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
	template<typename T, typename Compare, typename Alloc>
	void	swap(const set<T, Compare, Alloc> & x, const set<T, Compare, Alloc> & y)
	{
		x.swap(y);
	}
}

#endif