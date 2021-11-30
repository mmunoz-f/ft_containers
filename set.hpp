/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:32:28 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/30 20:00:33 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SET_H__
# define __SET_H__

# include <stddef.h>
# include <functional>
# include <memory>
# include "utils/pair.hpp"
# include "utils/red_black_tree.hpp"

namespace   ft {
	template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set {
		public:
			typedef	Key											key_value;
			typedef Key											value_type;

			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;

			typedef Compare										key_compare;
			typedef Compare										value_compare;

			typedef Allocator									allocator_type;

			typedef value_type&									reference;
			typedef const value_type&							const_reference;

			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;

		private:
			typedef tree<value_type, value_compare, Allocator>	Tree;
		public:
			typedef typename Tree::iterator						iterator;
			typedef typename Tree::const_iterator				const_iterator;
			typedef typename Tree::reverse_iterator				reverse_iterator;
			typedef typename Tree::const_reverse_iterator		const_reverse_iterator;

			set() : _tree(Compare(), Allocator()) {}
			explicit	set(const Compare &cmp, const Allocator &alloc = Allocator()) : _tree(cmp, alloc) {}

			template<class InputIt>
			set(InputIt first, InputIt last, const Compare &cmp = Compare(), const Allocator &alloc = Allocator()) : _tree(cmp, alloc) {
				insert(first, last);
			}

			set(const set &other) : _tree(other._tree._comp, other._tree._alloc) {
				insert(other.begin(), other.end());
			}

			~set() { clear(); }

			set	&operator=(const set &other) {
				if (this == &other)
					return (*this);
				clear();
				insert(other.begin(), other.end());
				return (*this);
			}

			allocator_type	get_allocator () const { return (_tree.get_allocator()); }

			iterator				begin() { return (_tree.begin()); }
			const_iterator			begin() const { return (_tree.begin()); }

			iterator				end() { return (_tree.end()); }
			const_iterator			end() const { return (_tree.end()); }

			reverse_iterator		rbegin() { return (_tree.rbegin()); }
			const_reverse_iterator	rbegin() const { return (_tree.rbegin()); }

			reverse_iterator		rend() { return (_tree.rend()); }
			const_reverse_iterator	rend() const { return (_tree.rend()); }

			bool		empty() const { return (_tree.empty()); }

			size_type	size() const { return (_tree.size()); }

			size_type	max_size() const { return (_tree.max_size()); }

			void	clear() {
				
			}

			ft::pair<iterator, bool>	insert(const value_type &value) {
				iterator	it;
				if ((it = find(value)) != end())
					return (ft::pair<iterator, bool>(it, false));
				return (_tree.insertNode(value));
			}
			iterator					insert(iterator hint, const value_type &value) {
				(void)hint; // se ignora porque se autobalancea
				iterator	it;
				if ((it = find(value)) != end())
					return (it);
				return (_tree.insertNode(value).first);
			}
			template<class InputIt>
			void						insert(InputIt first, InputIt last) {
				for (;first != last; first++)
					insert(*first);
			}

			void	erase(iterator pos) {
				_tree.deleteNode(pos.base());
			}
			void	erase(iterator first, iterator last) {
				iterator	next = first;
				next++;
				for (;first != last; next++) {
					erase(first);
					first = next;
				}
			}
			size_type	erase(const Key &key) {
				iterator	it;
				size_type	i = 0;
				for (; (it = find(key)) != end(); i++)
					erase(it);
				return (i);
			}

			void	swap(set &other) {
				_tree.swap(other._tree);
			}
			
			size_type	count(const Key &key) const {
				return (_tree.count(key));
			};

			iterator	find(const Key &key) {
				return (_tree.find(key));
			}
			const_iterator	find(const Key &key) const {
				return (_tree.find(key));
			}

			ft::pair<iterator, iterator>	equal_range(const Key &key) {
				return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const Key &key) const {
				return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}

			iterator	lower_bound(const Key &key) {
				return (_tree.lower_bound(key));
			}
			const_iterator	lower_bound(const Key &key) const {
				return (_tree.lower_bound(key));
			}

			key_compare	key_comp() const { return (Compare()); }

			value_compare	value_comp() const { return (value_compare(Compare())); }

		private:
			Tree	_tree;
	};

	template<class Key, class T, class Compare, class Allocator>
	bool	operator==(ft::set<T, Compare, Allocator> lhs, ft::set<T, Compare, Allocator> rhs) {
		typename ft::set<T, Compare, Allocator>::const_iterator	first1 = lhs.begin();
		typename ft::set<T, Compare, Allocator>::const_iterator	first2 = rhs.begin();
		for (;first1 != lhs.end() && first2 != rhs.end(); first1++, first2++)
			if (*first1 != *first2)
				return (false);
		return (first1 == lhs.end() && first2 == rhs.end());
	}
	template<class Key, class T, class Compare, class Allocator>
	bool	operator!=(ft::set<T, Compare, Allocator> lhs, ft::set<T, Compare, Allocator> rhs) { return !(lhs == rhs); }
	template<class Key, class T, class Compare, class Allocator>
	bool	operator<(ft::set<T, Compare, Allocator> lhs, ft::set<T, Compare, Allocator> rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template<class Key, class T, class Compare, class Allocator>
	bool	operator<=(ft::set<T, Compare, Allocator> lhs, ft::set<T, Compare, Allocator> rhs) { return !(rhs < lhs); }
	template<class Key, class T, class Compare, class Allocator>
	bool	operator>(ft::set<T, Compare, Allocator> lhs, ft::set<T, Compare, Allocator> rhs) { return (rhs < lhs); }
	template<class Key, class T, class Compare, class Allocator>
	bool	operator>=(ft::set<T, Compare, Allocator> lhs, ft::set<T, Compare, Allocator> rhs) { return !(lhs < rhs); }

	template<class Key, class T, class Compare, class Allocator>
	void	swap(ft::set<T, Compare, Allocator> &lhs, ft::set<T, Compare, Allocator> &rhs) {
		lhs.swap(rhs);
	}
}

#endif