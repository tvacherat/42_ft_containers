/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 11:45:17 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/16 20:59:22 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
 #define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

namespace ft
{
	/*
		Vector class template below
		Vectors are sequence containers representing arrays that can change in size.
		https://www.cplusplus.com/reference/vector/vector/
	*/
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef	T														value_type;
			typedef	Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;			
			typedef	ft::normal_iterator<pointer, vector>					iterator;
			typedef	ft::normal_iterator<const_pointer, vector>				const_iterator;
			typedef	ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef	size_t													size_type;
		
		private:
			allocator_type	m_alloc;
			size_type		m_capacity;
			pointer			m_start;
			size_type		m_size;

		public:
			explicit vector(const allocator_type & alloc = allocator_type())
				: m_alloc(alloc), m_capacity(0), m_start(NULL), m_size(0) {}
			explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
				: m_alloc(alloc), m_capacity(n), m_start(m_alloc.allocate(n)), m_size(n)
			{
				for (iterator it = begin(); it != end(); it++)
					m_alloc.construct(&(*it), val);
			}
			template <typename InputIterator>
         	vector(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type & alloc = allocator_type())
				: m_alloc(alloc), m_capacity(static_cast<size_type>(ft::distance(first, last))), m_start(m_alloc.allocate(m_capacity)), m_size(m_capacity)
			{
				for (iterator it = begin(); first != last; it++, first++)
					m_alloc.construct(&(*it), *first);
			}
			vector(const vector & x)
				: m_alloc(x.m_alloc), m_capacity(x.m_capacity), m_start(m_alloc.allocate(m_capacity)), m_size(x.m_size)
			{
				iterator	it = begin();

				for (const_iterator x_it = x.begin(); x_it != x.end(); it++, x_it++)
					m_alloc.construct(&(*it), *x_it);
			}
			~vector()
			{
				for (iterator it = begin(); it != end(); it++)
					m_alloc.destroy(&(*it));
				m_alloc.deallocate(m_start, m_capacity);
			}
			vector &	operator=(const vector & x)
			{
				if (this != &x)
				{
					if (x.size() <= m_capacity)
					{
						iterator	it = begin();
						while (m_size > x.m_size)
							pop_back();
						m_size = x.m_size;
						for (const_iterator x_it = x.begin(); x_it != x.end(); it++, x_it++)
							m_alloc.construct(&(*it), *x_it);
					}
					else
					{
						for (iterator it = begin(); it != end(); it++)
							m_alloc.destroy(&(*it));
						m_alloc.deallocate(m_start, m_capacity);
						m_start = m_alloc.allocate(x.m_size);
						m_capacity = x.m_size;
						m_size = x.m_size;
						iterator	it = begin();
						for (const_iterator x_it = x.begin(); x_it != x.end(); it++, x_it++)
							m_alloc.construct(&(*it), *x_it);
					}
				}
				return (*this);
			}
			template <typename InputIterator>
			void	assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
			{
				size_type	new_size = static_cast<size_type>(ft::distance(first, last));

				for (iterator it = begin(); it != end(); it++)
					m_alloc.destroy(&(*it));
				if (m_capacity < new_size)
				{
					m_alloc.deallocate(m_start, m_capacity);
					m_start = m_alloc.allocate(new_size);
					m_capacity = new_size;
				}
				m_size = new_size;
				for (iterator it = begin(); first != last; it++, first++)
					m_alloc.construct(&(*it), *first); 
			}
			void	assign(size_type n, const value_type & val)
			{
				for (iterator it = begin(); it != end(); it++)
					m_alloc.destroy(&(*it));
				if (m_capacity < n)
				{
					m_alloc.deallocate(m_start, m_capacity);
					m_start = m_alloc.allocate(n);
					m_capacity = n;
				}
				m_size = n;
				for (iterator it = begin(); it != end(); it++)
					m_alloc.construct(&(*it), val);
			}
			void	pop_back()
			{
				m_size--;
				m_alloc.destroy(m_start + m_size);
			}
			void	push_back(const value_type & val)
			{
				if (m_capacity <= m_size)
				{
					if (!m_capacity)
						reserve(1);
					else
						reserve(m_capacity * 2);
				}
				m_alloc.construct(m_start + m_size, val);
				m_size++;
			}
			void	reserve(size_type n)
			{
				if (n > m_capacity)
				{
					vector	tmp(*this);

					clear();
					m_alloc.deallocate(m_start, m_capacity);
					m_start = m_alloc.allocate(n);
					m_capacity = n;
					for (iterator it = tmp.begin(); it != tmp.end(); it++)
						push_back(*it);
				}
			}
			iterator	erase(iterator position)
			{
				if (position == end() - 1)
					pop_back();
				else
				{
					m_alloc.destroy(&(*position));
					for (iterator it = position; it != end() - 1; it++)
					{
						m_alloc.construct(&(*it), *(it + 1));
						m_alloc.destroy(&(*(it + 1)));
					}
					m_size--;
				}
				return (position);
			}
			iterator	erase(iterator first, iterator last)
			{
				for (iterator it = first; it != last; last--)
					erase(it);
				return (first);
			}
			iterator	insert(iterator position, const value_type & val)
			{
				difference_type	diff = position - begin();
				
				if (m_size + 1 > m_capacity)
				{
					/* MACOS
					if (m_capacity * 2 > m_size + 1)
						reserve(m_capacity * 2);
					else
						reserve(m_size + 1);
					*/
					if (m_size * 2 > m_size + 1)
						reserve(m_size * 2);
					else
						reserve(m_size + 1);
				}
				iterator	iter = end();
				for (; iter != begin() + diff; iter--)
				{
					m_alloc.construct(&(*iter), *(iter - 1));
					m_alloc.destroy(&(*(iter - 1)));
				}
				m_alloc.construct(&(*iter), val);
				m_size++;
				return (iter);
			}
			template <class InputIterator>
			void	insert(iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
			{
				difference_type	diff = position - begin();
				
				if (m_size + ft::distance(first, last) > m_capacity)
				{
					/* MACOS
					if (m_capacity * 2 > m_size + ft::distance(first, last))
						reserve(m_capacity * 2);
					else
						reserve(m_size + ft::distance(first, last));
					*/
					if (m_size * 2 > m_size + ft::distance(first, last))
						reserve(m_size * 2);
					else
						reserve(m_size + ft::distance(first, last));
				}
				for (difference_type i = 0; first != last; first++, i++)
					insert(begin() + diff + i, *first);
			}
			void	insert(iterator position, size_type n, const value_type & val)
			{
				difference_type	diff = position - begin();

				if (!n)
					return ;
				if (m_size + n > m_capacity)
				{
					/* MACOS
					if (m_capacity * 2 > m_size + n)
						reserve(m_capacity * 2);
					else
						reserve(m_size + n);
					*/
					if (m_size * 2 > m_size + n)
						reserve(m_size * 2);
					else
						reserve(m_size + n);
				}
				while (n--)
					insert(begin() + diff, val);
			}
			void	resize(size_type n, value_type val = value_type())
			{
				if (n < m_size)
					erase(end() - (m_size - n), end());
				else if (n > m_size)
					insert(end(), n - m_size, val);
			}
			void	swap(vector & x)
			{
				size_type	tmp_size = m_size;
				size_type	tmp_capacity = m_capacity;
				pointer		tmp_start = m_start;

				m_size = x.m_size;
				m_capacity = x.m_capacity;
				m_start = x.m_start;
				x.m_size = tmp_size;
				x.m_capacity = tmp_capacity;
				x.m_start = tmp_start;
			}
			iterator	begin()
			{
				return (iterator(m_start));
			}
			const_iterator	begin() const
			{
				return (const_iterator(m_start));
			}
			iterator	end()
			{
				return (iterator(m_start + m_size));
			}
			const_iterator	end() const
			{
				return (const_iterator(m_start + m_size));
			}
			reverse_iterator	rbegin()
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()));
			}
			reverse_iterator	rend()
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(begin()));
			}
			void clear()
			{
				for (iterator it = begin(); it != end(); it++)
					m_alloc.destroy(&(*it));
				m_size = 0;
			}
			bool empty() const
			{
				return (m_size == 0);
			}
			size_type	capacity() const
			{
				return (m_capacity);
			}
			size_type	size() const
			{
				return (m_size);
			}
			reference	front()
			{
				return (*m_start);
			}
			const_reference	front() const
			{
				return (*m_start);
			}
			reference	back()
			{
				return (*(m_start + m_size - 1));
			}
			const_reference	back() const
			{
				return (*(m_start + m_size - 1));
			}
			reference	at(size_type n)
			{
				if (n >= m_size)
					throw std::out_of_range("Out of range");
				return (*(m_start + n));
			}
			const_reference	at(size_type n) const
			{
				if (n >= m_size)
					throw std::out_of_range("Out of range");
				return (*(m_start + n));
			}
			allocator_type	get_allocator() const
			{
				return (m_alloc);
			}
			size_type	max_size() const
			{
				return (m_alloc.max_size());
			}
			reference	operator[](size_type n)
			{
				return (*(m_start + n));
			}
			const_reference	operator[](size_type n) const
			{
				return (*(m_start + n));
			}
	};
	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		else
			return (false);
	}
	template <typename T, typename Alloc>
  	bool operator!=(const vector<T, Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}
	template <typename T, typename Alloc>
  	bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <typename T, typename Alloc>
	bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}
	template <typename T, typename Alloc>
 	bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (rhs < lhs);
	}
	template <typename T, typename Alloc>
 	bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
	template <typename T, typename Alloc>
	void swap (vector<T, Alloc> & x, vector<T, Alloc> & y)
	{
		x.swap(y);
	}
}

#endif
