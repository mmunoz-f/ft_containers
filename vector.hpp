/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:29:07 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/12/06 19:39:40 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_H__
# define __VECTOR_H__

# include <stddef.h>
# include <memory>
# include <stdexcept>
# include "utils/utils.hpp"
# include "utils/pair.hpp"
# include "utils/vector_iterator.hpp"
# include "utils/reverse_iterator.hpp"

namespace ft {

	/* vector container redefinition */

	template<class T, class Allocator = std::allocator<T> >
	class	vector {

		public:

			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef ptrdiff_t								difference_type;

			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			typedef ft::vector_iterator<pointer>			iterator;
			typedef ft::vector_iterator<const_pointer>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			/* CONSTRUCTORS */

			vector() : _begin(), _end(), _end_cap(NULL, std::allocator<T>()) {}
			explicit	vector(const Allocator &alloc) : _begin(), _end(), _end_cap(NULL, alloc) {}
			explicit	vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator()) : _end_cap(NULL, alloc) {
				_begin = _end = _end_cap.second.allocate(count);
				_end_cap.first = _begin + count;
				insert(begin(), count, value);
			}
			template<class InputIt>
			vector(typename ft::enable_if<!ft::is_integral<InputIt>::value ,InputIt>::type first, InputIt last, const Allocator &alloc = Allocator()) : _end_cap(NULL, alloc) {
				_begin = _end = _end_cap.second.allocate(ft::distance(first, last));
				_end_cap.first = _begin + (ft::distance(first, last));
				insert(begin(), first, last);
			}
			vector(const vector &other) : _end_cap(NULL, other.get_allocator()) {
				_begin = _end =_end_cap.second.allocate(other.capacity());
				_end_cap.first = _begin + other.capacity();
				insert(begin(), other.begin(), other.end());
			}
			/* --------- */

			/* DESTRUCTOR */

			~vector() {
				_end_cap.second.deallocate(_begin, capacity());
			}
			/* --------- */


			/* ASSING OPERATOR */

			vector	&operator=(const vector &other) {
				if (this == &other)
					return (*this);
				_end_cap.second.deallocate(_begin, capacity());
				_end_cap.second = other.get_allocator();
				_begin = _end = _end_cap.second.allocate(other.capacity());
				_end_cap.first = _begin + other.capacity();
				insert(begin(), other.begin(), other.end());
				return (*this);
			}
			/* --------- */

			void	assign(size_type count, const T &value) {
				clear();
				insert(begin(), count, value);
			}
			template<class InputIt>
			void	assign(typename ft::enable_if<!ft::is_integral<InputIt>::value ,InputIt>::type first, InputIt last) {
				clear();
				insert(begin(), first, last);
			}

			allocator_type	get_allocator() const { return (_end_cap.second); }

			reference		at(size_type pos) {
				if (pos < 0 || (pos >= size()))
					throw std::out_of_range("");
				return (_begin[pos]);
			}
			const_reference	at(size_type pos) const {
				if (pos < 0 || (pos >= size()))
					throw std::out_of_range("");
				return (_begin[pos]);
			}


			/* ACCESS OPERATORS */

			reference	operator[](size_type pos) { return (_begin[pos]); }
			const_reference	operator[](size_type pos) const { return (_begin[pos]); }
			/* --------- */

			reference				front() { return (*_begin); }
			const_reference			front() const { return (*_begin); }
			reference				back() { return (*(_end - 1)); }
			const_reference			back() const { return (*(_end - 1)); }

			/* ITERATORS */

			iterator				begin() { return (iterator(_begin)); }
			const_iterator			begin() const { return (const_iterator(_begin)); }
			iterator				end() { return (iterator(_end)); }
			const_iterator			end() const { return (const_iterator(_end)); }

			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
			/* --------- */

			/* CAPACITY METHODS */

			bool	empty() const { return (_begin == _end); }
			size_type	size() const { return (_end - _begin); }
			size_type	max_size() const { return (_end_cap.second.max_size()); }

			void	reserve(size_type new_cap) {
				if (new_cap < capacity())
					return ;
				if (new_cap > max_size())
					throw	std::length_error("");
				iterator	old_begin = begin();
				iterator	old_end = end();
				_begin = _end = _end_cap.second.allocate(new_cap);
				_end_cap.first = _begin + new_cap;
				insert(begin(), old_begin, old_end);
				_end_cap.second.deallocate(old_begin.base(), ft::distance(old_begin, old_end));
			}

			size_type	capacity() const { return (_end_cap.first - _begin); }
			/* --------- */

			/* MODIFIER METHODS */

			void	clear() { erase(begin(), end()); }

			iterator	insert(iterator pos, const T &value) {
				if (_end == _end_cap.first) {
					difference_type	pos_val = ft::distance(begin(), pos);
					reserve((size() + 1) * 2);
					pos = begin() + pos_val;
				}
				for (iterator next = end(); next > pos; next--)
					_end_cap.second.construct(next.base(), *(next - 1));
				_end++;
				_end_cap.second.construct(pos.base(), value);
				return (pos);
			}
			void		insert(iterator pos, size_type count, const T &value) {
				for (size_type i = 0; i < count; i++, pos++)
					pos = insert(pos, value);
			}
			template<class InputIt>
			void		insert(iterator pos, typename ft::enable_if< !ft::is_integral<InputIt>::value ,InputIt>::type first, InputIt last) {
				for (; first != last; first++, pos++)
					pos = insert(pos, *first);
			}

			iterator	erase(iterator pos) {
				if (pos != end())
					_end_cap.second.destroy(pos.base());
				for (iterator next = pos; next + 1 < end(); next++)
					_end_cap.second.construct(next.base(), *(next + 1));
				_end--;
				return (pos);
			}
			iterator	erase(iterator first, iterator last) {
				for (; first != last; last--)
					erase(last - 1);
				return (last);
			}

			void	push_back(const T &value) { insert(end(), value); }
			void	pop_back() { erase(--end()); }

			void	resize(size_type count, T value = T()) {
				if (count > size())
					insert(end(), count - size(), value);
				else
					for (; size() - count;)
						erase(end() - 1);
			}

			void	swap(vector &other) {
				ft::swap(_begin, other._begin);
				ft::swap(_end, other._end);
				ft::swap(_end_cap, other._end_cap);
			}
			/* --------- */

		private:

			pointer							_begin;
			pointer							_end;
			ft::pair<pointer, Allocator>	_end_cap;
	};

	/* RELATIONAL OPERATORS */

	template< class T, class Alloc >
	bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		typename vector<T, Alloc>::const_iterator first1 = lhs.begin();
		typename vector<T, Alloc>::const_iterator first2 = rhs.begin();
		for (;first1 != lhs.end() && first2 != rhs.end() && *first1 == *first2; first1++, first2++);
		return (first1 == lhs.end() && first2 == rhs.end());
	}
	template< class T, class Alloc >
	bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) { return (!(lhs == rhs)); }
	template< class T, class Alloc >
	bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template< class T, class Alloc >
	bool	operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) { return !(rhs < lhs); }
	template< class T, class Alloc >
	bool	operator>( const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) { return (rhs < lhs); };
	template< class T, class Alloc >
	bool	operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs) { return !(lhs < rhs); }

	template< class T, class Alloc >
	void	swap(vector<T,Alloc> &lhs, vector<T,Alloc> &rhs) {
		lhs.swap(rhs);
	}
}

#endif
