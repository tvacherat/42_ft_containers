/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:04:45 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/20 00:13:58 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
 #define MAP_HPP

#include <memory>
#include "functional.hpp"
#include "btree.hpp"
#include "utility.hpp"

namespace ft
{
	/*
		Map class definition below
		Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order.
		https://www.cplusplus.com/reference/map/map/
	*/
	template <typename Key, typename T, typename Compare = ft::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
	
			class value_compare: public ft::binary_function<value_type, value_type, bool>
			{
				public:
					key_compare	comp;

					value_compare(key_compare c = key_compare())
						: comp(c) {}

					bool operator()(const value_type & x, const value_type & y) const
					{
						return (comp(x.first, y.first));
					}
			};
	
		private:
			typedef	ft::btree<value_type, value_compare, allocator_type>	_tree_type;
			
			_tree_type	m_tree;

		public:	
			typedef typename _tree_type::iterator							iterator;
			typedef typename _tree_type::const_iterator						const_iterator;
			typedef typename _tree_type::reverse_iterator					reverse_iterator;
			typedef typename _tree_type::const_reverse_iterator				const_reverse_iterator;
			typedef typename _tree_type::difference_type					difference_type;
			typedef	typename _tree_type::size_type							size_type;
			
			explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: m_tree(comp, alloc) {}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
				: m_tree(comp, alloc)
			{
				while (first != last)
				{
					if (m_tree.find(*first) == m_tree.end())
						m_tree.insert(*first);
					first++;
				}
			}
			map(const map & src)
				: m_tree(_tree_type(src.m_tree)) {}
			~map() {}
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
			size_type	count(const key_type & k) const
			{
				return (m_tree.find(ft::make_pair(k, mapped_type())) != m_tree.end() ? 1 : 0);
			}
			bool	empty() const
			{
				return (m_tree.empty());
			}
			ft::pair<iterator, iterator>	equal_range(const key_type & k)
			{
				return (m_tree.equal_range(ft::make_pair(k, mapped_type())));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type & k) const
			{
				return (m_tree.equal_range(ft::make_pair(k, mapped_type())));
			}
			iterator lower_bound(const key_type & k)
			{
				return (m_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}
			const_iterator lower_bound(const key_type & k) const
			{
				return (m_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}
			iterator upper_bound(const key_type & k)
			{
				return (m_tree.upper_bound(ft::make_pair(k, mapped_type())));
			}
			const_iterator upper_bound(const key_type & k) const
			{
				return (m_tree.upper_bound(ft::make_pair(k, mapped_type())));
			}
			void	erase(iterator position)
			{
				m_tree.erase(position);
			}
			size_type	erase(const key_type & k)
			{
				return (m_tree.erase(ft::make_pair(k, mapped_type())));
			}
			void	erase(iterator first, iterator last)
			{
				m_tree.erase(first, last);
			}
			iterator find(const key_type & k)
			{
				return (m_tree.find(ft::make_pair(k, mapped_type())));
			}
			const_iterator find(const key_type & k) const
			{
				return (m_tree.find(ft::make_pair(k, mapped_type())));
			}
			allocator_type	get_allocator() const
			{
				return (m_tree.get_allocator());
			}
			ft::pair<iterator, bool>	insert(const value_type & val)
			{
				iterator	it = m_tree.find(val);

				return (it == m_tree.end() ? ft::make_pair(m_tree.insert(val), true) : ft::make_pair(it, false));
			}
			iterator insert(iterator position, const value_type & val)
			{
				iterator	it = m_tree.find(val);

				return (it == m_tree.end() ? m_tree.insert(position, val) : it);
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
				return (m_tree.get_comparator().comp);
			}
			value_compare value_comp() const
			{
				return (m_tree.get_comparator());
			}
			size_type max_size() const
			{
				return (m_tree.max_size());
			}
			map &	operator=(const map & x)
			{
				if (this != &x)
					m_tree = x.m_tree;
				return (*this);
			}
			mapped_type &	operator[](const key_type& k)
			{
				return ((*((insert(ft::make_pair(k, mapped_type()))).first)).second);
			}
			void	swap(map & x)
			{
				m_tree.swap(x.m_tree);
			}
	};
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		else
			return (false);
	}
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (rhs < lhs);
	}
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
	template<typename Key, typename T, typename Compare, typename Alloc>
	void	swap(const map<Key, T, Compare, Alloc> & x, const map<Key, T, Compare, Alloc> & y)
	{
		x.swap(y);
	}
}

#endif