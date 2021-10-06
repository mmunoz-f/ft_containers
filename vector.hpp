/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:29:07 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/06 17:07:37 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_H__
# define __VECTOR_H__

# include <memory>
# include "utils/utils.hpp"
# include "utils/pair.hpp"
# include "utils/reverse_iterator.hpp"

namespace ft {

	/* vector RandomAccessIterator */

	template<class T>
	class vector_iterator {

		protected:
			T	_current;

		public:
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_categoty;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

			/* CONSTRUCTORS */

			vector_iterator() : _current() {}
			explicit	vector_iterator(T x) : _current(x) {}
			template<class U>
			vector_iterator(const vector_iterator<U> &other) : _current(other.base()) {}
			/* --------- */

			/* ASSIGN OPERATOR */

			template<class U>
			vector_iterator	&operator=(const vector_iterator<U> &other) {
				_current = other.base();
				return (*this);
			}
			/* --------- */

			T	base() const { return (_current); }

			/* ACCESS OPERATORS */

			reference	operator*() const {
				reference	tmp(*(this->base()));
				return (tmp);
			}
			pointer		operator->() const {
				pointer	tmp(this->base());
				return (tmp);
			}

			reference	operator[](difference_type n) const { return (_current[n]); }
			/* --------- */

			/* ADVANCES AND DECREMENTS OPERATORS */

			vector_iterator	&operator++() {
				++_current;
				return (*this);
			}
			vector_iterator	&operator--() {
				--_current;
				return (*this);
			}

			vector_iterator	operator++(int) {
				vector_iterator	tmp(*this);
				++_current;
				return (tmp);
			}
			vector_iterator	operator--(int) {
				vector_iterator	tmp(*this);
				--_current;
				return (tmp);
			}

			vector_iterator	operator+(difference_type n) const { return (vector_iterator(base() + n)); }
			vector_iterator	operator-(difference_type n) const { return (vector_iterator(base() - n)); }

			template<class U>
			vector_iterator	&operator+=(U n) { return (*this = *this + n); }
			template<class U>
			vector_iterator	&operator-=(U n) { return (*this = *this - n); }
			/* --------- */
	};

	/* COMPARE OPERATORS */

	template<class T, class U>
	bool	operator==(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter1.base() == Iter2.base()); }
	template<class T, class U>
	bool	operator!=(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return !(Iter1 == Iter2); }
	template<class T, class U>
	bool	operator<(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter1.base() < Iter2.base()); }
	template<class T, class U>
	bool	operator<=(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return !(Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>=(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return !(Iter1 < Iter2); }
	/* --------- */

	template<class T>
	vector_iterator<T>	operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T> &Iter) { return (Iter + n); }
	template<class T>
	typename vector_iterator<T>::difference_type	operator-(const vector_iterator<T> &Iter1, const vector_iterator<T> &Iter2) { return (Iter1.base() - Iter2.base()); }



	/* vector container redefinition */

	template<class T , class Allocator = std::allocator<T> >
	class	vector {

		public:

			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef std::size_t							size_type;
			typedef ptrdiff_t							difference_type;

			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;

			typedef ft::vector_iterator<T>				iterator;
			typedef ft::vector_iterator<const T>		const_iterator;
			typedef ft::reverse_iterator<T>				reverse_iterator;
			typedef ft::reverse_iterator<const T>		const_reverse_iterator;

			/* CONSTRUCTORS */

			vector() : _begin(), _end(), _end_cap() {}
			explicit	vector(const Allocator &alloc) : _begin(), _end(), _end_cap(NULL, alloc) {}
			explicit	vector(size_type count, const T & value = T(), const Allocator &alloc = Allocator()) : _end_cap(NULL, alloc) {
				_begin = alloc.allocate(count);
				_end = _end_cap.first = _begin + count;
				for (pointer i = _begin; i != _end; i++)
					_end_cap.second.construct(i, value);
			}
			template<class InputIt>
			vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()) : _end_cap(NULL, alloc) {
				_begin = alloc.allocate(first - last);
				_end = _end_cap.first = _begin + (first - last);
				for (pointer i = _begin; first != last; first++, last++)
					_end_cap.second.construct(i, *first);
			}
			vector(const vector &other) : _end_cap(NULL, other.get_allocator()) {
				_begin = _end_cap.second.allocate(other.size());
				_end = _end_cap = _begin + other.size();
				insert(begin(), other.begin(), other.end());
			}
			/* --------- */

			/* ASSING OPERATOR */

			vector	&operator=(const vector &other) {
				if (this == &other)
					return (*this);
				clear();
				_end_cap.second = other.get_allocator();
				insert(begin(), other.begin(), other.end());
				return (*this);
			}
			/* --------- */

			void	assign(size_type count, const T &value) {
				for (size_type i = 0; i < count; i++)
					_end_cap.second.construct(_begin[i], value);
			}
			template<class InputIt>
			void	assign(InputIt first, InputIt last) {
				for (size_type i = 0; first != last; first++, i++)
					_end_cap.second.construct(_begin[i], *first);
			}

			allocator_type	get_allocator() const { return (_end_cap.second); }

			reference		at(size_type pos) {
				if !(pos < size())
					throw std::out_of_range();
				return (_begin[pos]);
			}
			const_reference	at(size_type pos) const {
				if !(pos < size())
					throw std::out_of_range();
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
			const_iterator			cbegin() const { return (const_iterator(_begin)); }
			iterator				end() { return (iterator(_end)); }
			const_iterator			cend() const { return (const_iterator(_end)); }

			reverse_iterator		rbegin() { return (reverse_iterator(_end)); }
			const_reverse_iterator	crbegin() const { return (const_reverse_iterator(_end)); }
			reverse_iterator		rend() { return (reverse_iterator(_begin)); }
			const_reverse_iterator	crend() const { return (const_reverse_iterator(_begin)); }
			/* --------- */

			/* CAPACITY METHODS */

			bool	empty() const { return (_begin == _end); }
			size_type	size() const { return (_begin - _end); }
			size_type	max_size() const { return (_end_cap.second.max_size()); }

			void	reserve(size_type new_cap) {
				if (new_cap < capacity())
					return ;
				if (new_cap > max_size())
					throw	std::length_error();
				vector	tmp(new_cap, ,_end_cap.second);
				for (iterator i = begin(); i != end(); i++)
					tmp.push_back(*i);
				*this = tmp;
			}

			size_type	capacity() const { return (_begin - _end_cap.first); }
			/* --------- */

			/* MODIFIER METHODS */

			void	clear() { erase(begin(), end()); }

			iterator	insert(iterator pos, const T &value) {
				T	tmp = *pos;

				if (size() == capacity())
					resize(capacity() ? capacity() * 2 : 1);
				_end_cap.second.construct(pos.base(), value);
				for (; pos != end(); ++pos)
					ft::swap(*pos, tmp);
				*end() = tmp;
				_end++;
			}
			void		insert(iterator pos, size_type count, const T &value) {
				for (size_type i = 0; i < count; i++, pos++)
					insert(pos, value)
			}
			template<class InputIt>
			void		insert(iterator pos, InputIt first, InputIt last) {
				for (; first != last; first++, pos++)
					insert(pos, *first);
			}

			iterator	erase(iterator pos) {
				_end_cap.second.destroy(pos.base());
				for (; pos != end(); pos++)
					*pos = *(pos + 1);
				_end--;
			}
			iterator	erase(iterator first, iterator last) {
				for (; first != last; first++)
					erase(first);
			}

			void	push_back(const T &value) { insert(end(), value); }
			void	pop_back() { erase(end()); }

			void	resize(size_type count, T value = T()) {
				if (count <= size())
					insert(_end, count - size(), value);
				else
					for (; size() - count;)
						erase(end() - 1), ;
			}

			void	swap(vector &other) {
				pointer	tmp;

				tmp =  _begin;
				_begin = other.begin().base();
				other.begin() = tmp;
				tmp = _end;
				_end = other.end().base();
				other.end() = tmp;
				tmp = _end_cap.first;
				_end_cap.first = _begin + other.capacity();/////???????
			}
			/* --------- */

		private:

			pointer							_begin;
			pointer							_end;
			ft::pair<pointer, Allocator>	_end_cap;
	};

}

#endif
