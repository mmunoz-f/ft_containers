/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:59:50 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/21 20:04:48 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_H__
# define __MAP_H__

# include <stddef.h>
# include <functional>
# include <memory>
# include "utils/pair.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/red_black_tree.hpp"

namespace ft {

	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class	map {

		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;

			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			class	value_compare {
				protected:
					key_compare	comp;
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					value_compare(key_compare c) : comp(c) {}

					bool	operator()(const value_type &lhs, const value_type &rhs) const { return (comp(lhs.first, rhs.first)); }
			};

			typedef ft::tree<value_type, value_compare, Allocator>	Tree;
			typedef typename Tree::iterator							iterator;
			typedef typename Tree::const_iterator					const_iterator;
			typedef typename Tree::reverse_iterator					reverse_iterator;
			typedef typename Tree::const_reverse_iterator			const_reverse_iterator;

			/* CONSTRUCTORS */

			map() : _tree(value_compare(Compare()), Allocator()) {}
			explicit	map(const Compare &comp, const Allocator &alloc = Allocator()) : _tree(value_compare(comp), alloc) {}

			template<class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator &alloc = Allocator()) : _tree(value_compare(comp), alloc) {
				insert(first, last);
			}
			map(const map &other) : _tree(other._tree._comp, other._tree._alloc) {
				insert(other.begin(), other.end());
			}
			/* --------- */

			/* DESTRUCTOR */

			~map() { clear(); }
			/* --------- */

			/* ASSIGN OPERATOR */

			map	&operator=(const map &other) {
				if (this == &other)
					return (*this);
				// TODO clear
				insert(other.begin(), other.end());
				return (*this);
			}
			/* --------- */

			allocator_type	get_allocator() const { return (_tree.get_allocator()); }

			/* ELEMENT ACCESS */

			mapped_type	&at(const Key &key) {
				iterator	it;
				if ((it = find(key)) != end())
					return (it->second);
				throw std::out_of_range("");
			}
			mapped_type	&at(const Key &key) const {
				const_iterator	it;
				if ((it = find(key)) != end())
					return (it->second);
				throw std::out_of_range("");
			}

			mapped_type	&operator[](const Key &key) {
				iterator	it;
				if ((it = find(key)) != end())
					return (it->second);
				return (insert(value_type(key, mapped_type())).first->second);
			}
			/* --------- */

			/* ITERATORS */

			iterator				begin() { return (_tree.begin()); }
			const_iterator			begin() const { return (_tree.begin()); }

			iterator				end() { return (_tree.end()); }
			const_iterator			end() const { return (_tree.end()); }

			reverse_iterator		rbegin() { return (_tree.rbegin()); }
			const_reverse_iterator	rbegin() const { return (_tree.rbegin()); }

			reverse_iterator		rend() { return (_tree.rend()); }
			const_reverse_iterator	rend() const { return (_tree.rend()); }
			/* --------- */

			/* CAPACITY */

			bool	empty() const { return (_tree.empty()); }

			size_type	size() const { return (_tree.size()); }

			size_type	max_size() const { return (_tree.max_size()); }
			/* --------- */

			/* MODIFIERS */

			void	clear() {
			} // TODO needs check on deleteNode

			ft::pair<iterator, bool>	insert(const value_type &value) {
				iterator	it;
				if ((it = find(value.first)) != end())
					return (ft::pair<iterator, bool>(it, false));
				return (_tree.insertNode(value));
			}
			iterator	insert(iterator hint, const value_type &value) {
				(void)hint; // se ignora porque se autobalancea
				iterator	it;
				if ((it = find(value.first)) != end())
					return (it);
				return (_tree.insertNode(value).first);
			}
			template<class InputIt>
			void	insert(InputIt first, InputIt last) {
				for (;first != last; first++)
					insert(*first);
			}

			void	erase(iterator pos) {
				_tree.deleteNode(pos.base());
			}
			void	erase(iterator first, iterator last) {
				for (;first != last; first++)
					erase(first);
			}
			size_type	erase(const Key &key) {
				iterator	it;
				size_type	i = 0;
				if ((it = find(key)) != end())
					erase(it);
				return (i);
			}

			void	swap(map &other) {
				ft::swap(*this, other);
			}
			/* --------- */

			/* LOOKUP */

			size_type	count(const Key &key) const {
				return (_tree.count(value_type(key, T())));
			};

			iterator	find(const Key &key) {
				return (_tree.find(value_type(key, T())));
			}
			const_iterator	find(const Key &key) const {
				return (_tree.find(value_type(key, T())));
			}

			ft::pair<iterator, iterator>	equal_range(const Key &key) {
				return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const Key &key) const {
				return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}

			iterator	lower_bound(const Key &key) { // TODO rework
				for (iterator it = begin(); it != end(); it++)
					if (!Compare()(it->first, key))
						return (it);
				return (end());
			}
			const_iterator	lower_bound(const Key &key) const {
				for (const_iterator it = begin(); it != end(); it++)
					if (!Compare()(it->first, key))
						return (it);
				return (end());
			}

			iterator	upper_bound(const Key &key) { // TODO rework
				for (iterator it = begin(); it != end(); it++)
					if (Compare()(key, it->first)) 
						return (it);
				return (end());
			}
			const_iterator	upper_bound(const Key &key) const {
				for (const_iterator it = begin(); it != end(); it++)
					if (Compare()(key, it->first)) 
						return (it);
				return (end());
			}
			/* --------- */

			/* OBSERVERS */

			key_compare	key_comp() const { return (Compare()); }

			value_compare	value_comp() const { return (value_compare(Compare())); }
			/* --------- */

			void	print() const { _tree.print(); } // TODO tmp

		private:
			Tree	_tree;
	};

	template<class Key, class T, class Compare, class Allocator>
	bool	operator==(ft::map<Key, T, Compare, Allocator> lhs, ft::map<Key, T, Compare, Allocator> rhs) {
		typename ft::map<Key, T, Compare, Allocator>::const_iterator	first1 = lhs.begin();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator	first2 = rhs.begin();
		for (;first1 != lhs.end() && first2 != rhs.end(); first1++, first2++)
			if (*first1 != *first2)
				return (false);
		return (first1 == lhs.end() && first2 == rhs.end());
	}
	template<class Key, class T, class Compare, class Allocator>
	bool	operator!=(ft::map<Key, T, Compare, Allocator> lhs, ft::map<Key, T, Compare, Allocator> rhs) { return !(lhs == rhs); }
	template<class Key, class T, class Compare, class Allocator>
	bool	operator<(ft::map<Key, T, Compare, Allocator> lhs, ft::map<Key, T, Compare, Allocator> rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template<class Key, class T, class Compare, class Allocator>
	bool	operator<=(ft::map<Key, T, Compare, Allocator> lhs, ft::map<Key, T, Compare, Allocator> rhs) { return !(rhs < lhs); }
	template<class Key, class T, class Compare, class Allocator>
	bool	operator>(ft::map<Key, T, Compare, Allocator> lhs, ft::map<Key, T, Compare, Allocator> rhs) { return (rhs < lhs); }
	template<class Key, class T, class Compare, class Allocator>
	bool	operator>=(ft::map<Key, T, Compare, Allocator> lhs, ft::map<Key, T, Compare, Allocator> rhs) { return !(lhs < rhs); }

	template<class Key, class T, class Compare, class Allocator>
	void	swap(ft::map<Key, T, Compare, Allocator> lhs, ft::map<Key, T, Compare, Allocator> rhs) {
		lhs.swap(rhs);
	}
}

#endif
