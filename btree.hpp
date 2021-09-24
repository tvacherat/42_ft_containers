/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvachera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:16:24 by tvachera          #+#    #+#             */
/*   Updated: 2021/09/21 14:19:31 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_HPP
 #define BTREE_HPP

#include <memory> //std::allocator
#include <cstddef> // ptrdiff_t
#include <stdexcept> // logic_error
#include <string>
#include <limits>
#include "iterator.hpp"
#include "functional.hpp"
#include "utility.hpp"
#include "algorithm.hpp"

namespace ft
{
	enum	e_rbcolor
	{
		RED = false,
		BLACK = true
	};
	/*
		btree_node classe defintion
	*/
	template<typename T>
	struct btree_node
	{
			T			value;
			btree_node	*parent;
			btree_node	*left;
			btree_node	*right;
			e_rbcolor	color;

			btree_node(const T & v, const e_rbcolor & c, btree_node *p = NULL, btree_node *l = NULL, btree_node *r = NULL)
				: value(v), parent(p), left(l), right(r),  color(c) {}
	};

	template<typename T>
	class btree_iterator
		: public ft::iterator<typename ft::bidirectionnal_iterator_tag, T, ptrdiff_t, T *, T &>
	{
		public:
			typedef btree_node<T>								iterator_type;
			typedef ptrdiff_t									difference_type;
			typedef T											value_type;
			typedef T *											pointer;
			typedef T &											reference;
			typedef typename ft::bidirectionnal_iterator_tag	iterator_category;
		
		protected:
			iterator_type	*m_current;

		public:
			btree_iterator()
				: m_current(NULL) {}
			explicit btree_iterator(iterator_type *node)
				: m_current(node) {}
			btree_iterator(const btree_iterator & src)
				: m_current(src.base()) {}
			~btree_iterator() {}

			iterator_type	*base(void) const
			{
				return (m_current);
			}
			reference	operator*(void) const
			{
				return (m_current->value);
			}
			pointer	operator->(void) const
			{
				return (&(operator*()));
			}
			btree_iterator &	operator++(void)
			{
				iterator_type	*tmp;

				if (m_current->right)
				{
					m_current = m_current->right;
					while (m_current->left)
						m_current = m_current->left;
				}
				else
				{
					tmp = m_current->parent;
					while (m_current == tmp->right)
					{
						m_current = tmp;
						tmp = tmp->parent;
					}
					if (m_current->right != tmp)
						m_current = tmp;
				}
				return (*this);
			}
			btree_iterator operator++(int)
			{
				btree_iterator temp(*this);

				operator++();
				return (temp);
			}
			btree_iterator &	operator--(void)
			{
				iterator_type	*tmp;

				if (m_current->left)
				{
					m_current = m_current->left;
					while (m_current->right)
						m_current = m_current->right;
				}
				else
				{
					tmp = m_current->parent;
					while (m_current == tmp->left)
					{
						m_current = tmp;
						tmp = tmp->parent;
					}
					if (m_current->left != tmp)
						m_current = tmp;
				}
				return (*this);
			}
			btree_iterator operator--(int)
			{
				btree_iterator temp(*this);

				operator--();
				return (temp);
			}
		
	};
	template <typename T>
	bool	operator==(const btree_iterator<T> & lhs, const btree_iterator<T> & rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T>
	bool	operator!=(const btree_iterator<T> & lhs, const btree_iterator<T> & rhs)
	{
		return (!(lhs == rhs));
	}
	
	template<typename T>
	class btree_const_iterator
		: public ft::iterator<typename ft::bidirectionnal_iterator_tag, T, ptrdiff_t, const T *, const T &>
	{
		public:
			typedef btree_node<T>								iterator_type;
			typedef ptrdiff_t									difference_type;
			typedef T											value_type;
			typedef const T *									pointer;
			typedef const T &									reference;
			typedef typename ft::bidirectionnal_iterator_tag	iterator_category;
		
		protected:
			iterator_type	*m_current;

		public:
			btree_const_iterator()
				: m_current(NULL) {}
			explicit btree_const_iterator(iterator_type *node)
				: m_current(node) {}
			btree_const_iterator(const btree_iterator<T> & src)
				: m_current(src.base()) {}
			btree_const_iterator(const btree_const_iterator<T> & src)
				: m_current(src.base()) {}
			~btree_const_iterator() {}

			iterator_type	*base(void) const
			{
				return (m_current);
			}
			reference	operator*(void) const
			{
				return (m_current->value);
			}
			pointer	operator->(void) const
			{
				return (&(operator*()));
			}
			btree_const_iterator &	operator++(void)
			{
				iterator_type	*tmp;

				if (m_current->right)
				{
					m_current = m_current->right;
					while (m_current->left)
						m_current = m_current->left;
				}
				else
				{
					tmp = m_current->parent;
					while (m_current == tmp->right)
					{
						m_current = tmp;
						tmp = tmp->parent;
					}
					if (m_current->right != tmp)
						m_current = tmp;
				}
				return (*this);
			}
			btree_const_iterator operator++(int)
			{
				btree_const_iterator temp(*this);

				operator++();
				return (temp);
			}
			btree_const_iterator &	operator--(void)
			{
				iterator_type	*tmp;

				if (m_current->left)
				{
					m_current = m_current->left;
					while (m_current->right)
						m_current = m_current->right;
				}
				else
				{
					tmp = m_current->parent;
					while (m_current == tmp->left)
					{
						m_current = tmp;
						tmp = tmp->parent;
					}
					if (m_current->left != tmp)
						m_current = tmp;
				}
				return (*this);
			}
			btree_const_iterator operator--(int)
			{
				btree_const_iterator temp(*this);

				operator--();
				return (temp);
			}
			bool	operator==(const btree_const_iterator & x) const
			{
				return (m_current == x.m_current);
			}
			bool	operator!=(const btree_const_iterator & x) const
			{
				return (m_current != x.m_current);
			}
		
	};
	template <typename T>
	bool	operator==(const btree_iterator<T> & lhs, const btree_const_iterator<T> & rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T>
	bool	operator!=(const btree_iterator<T> & lhs, const btree_const_iterator<T> & rhs)
	{
		return (!(lhs == rhs));
	}
	/*
		btree (red and black - autobalanced) class definition
		https://www.codesdope.com/course/data-structures-binary-trees/ for help
	*/
	enum	e_btree_travel_mode
	{
		PREFIX,
		INFIX,
		SUFFIX
	};

	template<typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class btree
	{
		public:
			typedef	T															value_type;
			typedef btree_node<value_type>										node_type;
			typedef	Compare														compare_type;
			typedef	Alloc														allocator_type;
			typedef typename Alloc::template rebind<node_type>::other 			node_allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;			
			typedef	btree_iterator<value_type>									iterator;
			typedef	btree_const_iterator<value_type>							const_iterator;
			typedef	ft::reverse_iterator<iterator>								reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef	size_t														size_type;
			typedef e_rbcolor													color_type;
			typedef	e_btree_travel_mode											travel_mode;

			class EmptyTreeException: public std::logic_error
			{
				explicit EmptyTreeException(const std::string & what_arg);
			};
			
		private:
			compare_type		m_comp;
			allocator_type		m_val_alloc;
			node_allocator_type	m_node_alloc;
			node_type			*m_root;
			node_type			*m_head;

		public:
			btree(const compare_type & comp = compare_type(), const allocator_type & v_alloc = allocator_type(), const node_allocator_type & n_alloc = node_allocator_type())
				: m_comp(comp), m_val_alloc(v_alloc), m_node_alloc(n_alloc), m_root(NULL), m_head(_construct_node(value_type())) {}
			btree(const btree & src)
				: m_comp(src.m_comp), m_val_alloc(src.m_val_alloc), m_node_alloc(src.m_node_alloc), m_root(NULL), m_head(_construct_node(value_type()))
			{
				for (const_iterator it = src.begin(); it != src.end(); it++)
					insert(*it);
			}
			~btree()
			{
				clear();
				_destruct_node(m_head);
			}

			iterator	insert(const value_type & value)
			{
				if (!m_root)
				{
					m_root = _construct_node(value, BLACK);
					m_head->parent = m_root;
					m_head->left = m_root;
					m_head->right = m_root;
					m_root->parent = m_head;
					return (iterator(m_root));
				}
				else
				{
					m_root->parent = NULL;
					node_type *node = _construct_node(value);
					_insert(node);
					m_head->parent = m_root;
					m_head->left = m_root;
					m_head->right = m_root;
					m_root->parent = m_head;
					return (find(value));
				}
			}
			iterator insert(iterator position, const value_type & value)
			{
				(void)position; // Need optimisation

				return (insert(value));
			}
			size_type	erase(const value_type & value)
			{
				size_type	nb = 0;
				node_type	*node = _find(m_root, value);

				m_root->parent = NULL;
				while (node)
				{
					_erase(node);
					nb++;
					node = _find(m_root, value);
				}
				m_head->parent = m_root;
				m_head->left = m_root;
				m_head->right = m_root;
				if (m_root)
					m_root->parent = m_head;
				return (nb);
			}
			void	erase(iterator position)
			{
				node_type	*node = position.base();

				if (node && node != m_head)
				{
					m_root->parent = NULL;
					_erase(node);
					m_head->parent = m_root;
					m_head->left = m_root;
					m_head->right = m_root;
					if (m_root)
						m_root->parent = m_head;
				}
			}
			void	erase(iterator first, iterator last)
			{
				node_type	*node;

				while (first != last)
				{
					node = first.base();
					first++;
					if (node && node != m_head)
					{
						m_root->parent = NULL;
						_erase(node);
						m_head->parent = m_root;
						m_head->left = m_root;
						m_head->right = m_root;
						if (m_root)
							m_root->parent = m_head;
					}
				}
			}
			btree &	operator=(const btree & x)
			{
				if (this != &x)
				{
					clear();
					for (const_iterator it = x.begin(); it != x.end(); it++)
						insert(*it);
				}
				return (*this);
			}
			iterator	find(const value_type & value)
			{
				node_type	*node = _find(m_root, value);
	
				return (node ? iterator(node) : end());
			}
			const_iterator	find(const value_type & value) const
			{
				node_type	*node = _find(m_root, value);
	
				return (node ? const_iterator(node) : end());
			}
			void	clear(void)
			{
				if (m_root)
				{
					_clear(m_root);
					m_root = NULL;
					m_head->parent = NULL;
					m_head->left = NULL;
					m_head->right = NULL;
				}
			}
			iterator	begin(void)
			{
				if (m_root)
					return (iterator(_min(m_root)));
				else
					return (end());
			}
			const_iterator	begin(void) const
			{
				if (m_root)
					return (const_iterator(_min(m_root)));
				else
					return (end());
			}
			iterator	end(void)
			{
				return (iterator(m_head));
			}
			const_iterator	end(void) const
			{
				return (const_iterator(m_head));
			}
			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(end()));
			}
			reverse_iterator	rend(void)
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(begin()));
			}
			allocator_type	get_allocator() const
			{
				return (m_val_alloc);
			}
			compare_type	get_comparator() const
			{
				return (m_comp);
			}
			bool	empty(void) const
			{
				return (m_root ? false : true);
			}
			size_type	size(void) const
			{
				return (m_root ? _size(m_root) : 0);
			}
			size_type	max_size(void) const
			{
				return (m_node_alloc.max_size());
			}
			size_type	levels(void) const
			{
				return (m_root ? _levels(m_root) : 0);
			}
			void	apply(void (*applyf)(value_type &), const travel_mode & mode = INFIX)
			{
				if (!m_root)
					return ;
				if (mode == INFIX)
					return (_apply_infix(m_root, applyf));
				else if (mode == PREFIX)
					return (_apply_prefix(m_root, applyf));
				else
					return (_apply_suffix(m_root, applyf));
			}
			value_type	min(void) const
			{
				if (m_root)
					return (_min(m_root)->value);
				else
					throw btree::EmptyTreeException("Empty btree when calling min()");
			}
			value_type	max(void) const
			{
				if (m_root)
					return (_max(m_root)->value);
				else
					throw btree::EmptyTreeException("Empty btree when calling max()");
			}
			iterator	lower_bound(const value_type & k)
			{
				iterator	it = begin();

				while (it != end() && m_comp(*it, k))
					it++;
				return (it);
			}
			const_iterator lower_bound(const value_type & k) const
			{
				const_iterator	it = begin();

				while (it != end() && m_comp(*it, k))
					it++;
				return (it);
			}
			iterator	upper_bound(const value_type & k)
			{
				iterator	it = begin();

				while (it != end() && !m_comp(k, *it))
					it++;
				return (it);
			}
			const_iterator upper_bound(const value_type & k) const
			{
				const_iterator	it = begin();

				while (it != end() && !m_comp(k, *it))
					it++;
				return (it);
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const value_type & k) const
			{
				return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}
			ft::pair<iterator, iterator>	equal_range(const value_type & k)
			{
				return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
			void swap(btree & x)
			{
				node_type	*tmp = m_root;
				node_type	*tmpn = m_head;

				m_root = x.m_root;
				m_head = x.m_head;
				x.m_root = tmp;
				x.m_head = tmpn;
			}

		private:
			node_type	*_construct_node(const value_type & value, const color_type & color = RED)
			{
				node_type	*node = NULL;

				try
				{
					node = m_node_alloc.allocate(1);
					m_node_alloc.construct(node, node_type(value, color));
					m_val_alloc.construct(&node->value, value);
				}
				catch (std::exception & e)
				{
					_destruct_node(node);
					node = NULL;
					throw ;
				}
				return (node);
			}
			void	_destruct_node(node_type *node)
			{
				if (node)
				{
					m_val_alloc.destroy(&node->value);
					m_node_alloc.deallocate(node, 1);
				}
			}
			node_type	*_min(node_type *root) const
			{
				if (!root)
					return (NULL);
				while (root->left)
					root = root->left;
				return (root);
			}
			node_type	*_max(node_type *root) const
			{
				if (!root)
					return (NULL);
				while (root->right)
					root = root->right;
				return (root);
			}
			node_type	*_grandparent(const node_type *node) const
			{
				node_type	*p = node->parent;

				if (!p)
					return (NULL);
				return (p->parent);
			}
			node_type	*_brother(const node_type *node) const
			{
				node_type	*p = node->parent;

				if (!p)
					return (NULL);
				else if (p == p->left)
					return (p->right);
				else
					return (p->left);
			}
			node_type	*_uncle(const node_type *node) const
			{
				node_type	*p = node->parent;
				node_type	*g = _grandparent(node);

				if (!g)
					return (NULL);
				return (_brother(p));
			}			
			/*
				Tree insertion
			*/
			void	_insert(node_type *z)
			{
				node_type	*y = NULL;
				node_type	*temp = m_root;

				while (temp)
				{
  					y = temp;
					if (m_comp(z->value, temp->value))
    					temp = temp->left;
  					else
    					temp = temp->right;
				}
				z->parent = y;
				if (!y)
 					m_root = z;
				else if (m_comp(z->value, y->value))
  					y->left = z;
				else
					y->right = z;
				z->right = NULL;
				z->left = NULL;
				_insert_fixup(z);
			}
			void	_insert_fixup(node_type *node)
			{
				node_type	*parent = NULL;
    			node_type	*grandparent = NULL;
           	 	node_type	*uncle = NULL;
                color_type	tmp;

    			while (node != m_root && node->color == RED && node->parent->color == RED)
    			{
        			parent = node->parent;
        			grandparent = _grandparent(node);
        			if (parent == grandparent->left)
        			{
           	 			uncle = grandparent->right;
            			if (uncle && uncle->color == RED)
            			{
                			grandparent->color = RED;
                			parent->color = BLACK;
            			    uncle->color = BLACK;
            			    node = grandparent;
            			}
			            else
			            {
                			if (node == parent->right)
                			{
                			    _rotate_left(parent);
                    			node = parent;
                    			parent = node->parent;
                			}
                			_rotate_right(grandparent);
                			tmp = parent->color;
                			parent->color = grandparent->color;
                			grandparent->color = tmp;
                			node = parent;
            			}
        			}
        			else 
        			{
            			uncle = grandparent->left;
            			if (uncle && uncle->color == RED)
            			{
            			    grandparent->color = RED;
            			    parent->color = BLACK;
            			    uncle->color = BLACK;
            			    node = grandparent;
            			}
            			else
            			{
                			if (node == parent->left)
               				{
                 			   _rotate_right(parent);
                    			node = parent;
                    			parent = node->parent;
                			}
                			_rotate_left(grandparent);
                			tmp = parent->color;
                			parent->color = grandparent->color;
                			grandparent->color = tmp;
                			node = parent;
            			}
        			}
    			}
    			m_root->color = BLACK;
			}
			/*
				Tree deletion
			*/
			void	_erase(node_type *z)
			{
				node_type	*x;
    			node_type	*y = z;
    			color_type 	tmp = y->color;

    			if (!z->left)
    			{
        			x = z->right;
        			_transplant(z, z->right);
    			}
    			else if (!z->right)
    			{
     		   		x = z->left;
        			_transplant(z, z->left);
    			}
    			else
    			{
        			y = _min(z->right);
        			tmp = y->color;
        			x = y->right;
        			if (x && y->parent == z)
            			x->parent = y;
        			else if (y->parent != z)
        			{
            			_transplant(y, y->right);
            			y->right = z->right;
            			y->right->parent = y;
        			}	
        			_transplant(z, y);
        			y->left = z->left;
        			y->left->parent = y;
        			y->color = z->color;
    			}
    			if (tmp == BLACK)
    		    	_delete_fixup(x); 
    			_destruct_node(z);
			}
			void	_transplant(node_type *u, node_type *v)
			{
				if (!u->parent)
    				m_root = v; 
    			else if (u == u->parent->left)
        			u->parent->left = v;
    			else
        			u->parent->right = v;
				if (v)
					v->parent = u->parent;
			}
			void	_delete_fixup(node_type *node)
			{
				node_type	*w = NULL;

				while (node && node != m_root && node->color == BLACK)
    			{
        			if (node == node->parent->left)
        			{
            			w = node->parent->right;
            			if (w->color == RED)
            			{
                			w->color = BLACK;
                			node->parent->color = RED;
                			_rotate_left(node->parent);
                			w = node->parent->right;
            			}
            			if (w->left->color == BLACK && w->right->color == BLACK)
            			{
            				w->color = RED;
            	    		node = node->parent;
            			}
            			else if (w->right->color == BLACK)
            			{
            			    w->left->color = BLACK;
            			    w->color = RED;
            			    _rotate_right(w);
            			    w = node->parent->right;
            			}
            			else
            			{
            				w->color = node->parent->color;
                			node->parent->color = BLACK;
                			w->right->color = BLACK;
                			_rotate_left(node->parent);
                			node = m_root;
            			}
        			}
        			else
        			{
            			w = node->parent->left;
            			if (w->color == RED)
            			{
            			    w->color = BLACK;
            			    node->parent->color = RED;
            			    _rotate_right(node->parent);
            			    w = node->parent->left;
            			}
            			if (w->right->color == BLACK && w->left->color == BLACK)
            			{
            				w->color = RED;
                			node = node->parent;
            			}
            			else if (w->left->color == BLACK)
            			{
            			    w->right->color = BLACK;
            			    w->color = RED;
            			    _rotate_left(w);
           		 		    w = node->parent->left;
            			}
            			else
            			{
            			    w->color = node->parent->color;
            			    node->parent->color = BLACK;
            			    w->left->color = BLACK;
            			    _rotate_right(node->parent);
            			    node = m_root;
            			}
        			}
    			}
				if (node)
    				node->color = BLACK;
			}
			/*
				Tree rotations
			*/
			void	_rotate_left(node_type *x)
			{
				node_type *y = x->right;
				
				x->right = y->left;
				if (y->left)
  					y->left->parent = x;
				y->parent = x->parent;
				if (!x->parent)
  					m_root = y;
				else if (x == x->parent->left)
  					x->parent->left = y;
				else
  					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}
			void	_rotate_right(node_type *x)
			{
				node_type *y = x->left;
				
				x->left = y->right;
				if (y->right)
 			 		y->right->parent = x;
				y->parent = x->parent;
				if (!x->parent)
					m_root = y;
				else if (x == x->parent->right)
  					x->parent->right = y;
				else
 			 		x->parent->left = y;
				y->right = x;
				x->parent = y;
			}
			/*
				recursive functions
			*/
			node_type	*_find(node_type *root, const value_type & val) const
			{
				if (!root)
					return (NULL);
				if (m_comp(val, root->value))
					return (_find(root->left, val));
				else if (m_comp(root->value, val))
					return (_find(root->right, val));
				else
					return (root);
			}
			size_type	_size(node_type *root) const
			{
				if (!root)
					return (0);
				return (1 + _size(root->left) + _size(root->right));
			}
			size_type	_levels(node_type *root) const
			{
				size_type	count = 0;
				size_type	tmp;

				if (!root)
					return (0);
				if (root->left)
				{
					tmp = _levels(root->left);
					count < tmp ? count = tmp : 0;
				}
				if (root->right)
				{
					tmp = _levels(root->right);
					count < tmp ? count = tmp : 0;
				}
				return (count + 1);
			}
			void	_clear(node_type *root)
			{
				if (!root)
					return ;
				_clear(root->left);
				_clear(root->right);
				_destruct_node(root);
			}
			void	_apply_prefix(node_type *root, void (*applyf)(value_type &))
			{
				applyf(root->value);
				if (root->left)
					_apply_prefix(root->left, applyf);
				if (root->right)
					_apply_prefix(root->right, applyf);
			}
			void	_apply_infix(node_type *root, void (*applyf)(value_type &))
			{
				if (root->left)
					_apply_infix(root->left, applyf);
				(*applyf)(root->value);
				if (root->right)
					_apply_infix(root->right, applyf);
			}
			void	_apply_suffix(node_type *root, void (*applyf)(value_type &))
			{
				if (root->left)
					_apply_suffix(root->left, applyf);
				if (root->right)
					_apply_suffix(root->right, applyf);
				(*applyf)(root->value);
			}	
	};
	template<typename T, typename Compare, typename Alloc>
	bool	operator==(const btree<T, Compare, Alloc> & lhs, const btree<T, Compare, Alloc> & rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		else
			return (false);
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator!=(const btree<T, Compare, Alloc> & lhs, const btree<T, Compare, Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator<(const btree<T, Compare, Alloc> & lhs, const btree<T, Compare, Alloc> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator<=(const btree<T, Compare, Alloc> & lhs, const btree<T, Compare, Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator>(const btree<T, Compare, Alloc> & lhs, const btree<T, Compare, Alloc> & rhs)
	{
		return (rhs < lhs);
	}
	template<typename T, typename Compare, typename Alloc>
	bool	operator>=(const btree<T, Compare, Alloc> & lhs, const btree<T, Compare, Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
	template<typename T, typename Compare, typename Alloc>
  	void	swap(btree<T, Compare, Alloc> & x, btree<T, Compare, Alloc> & y)
	{
		x.swap(y);
	}
}

#endif