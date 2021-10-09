/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:29:07 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/09 20:31:02 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_H__
# define __VECTOR_H__

# include <memory>
# include <stdexcept>
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
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
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
	template<class T, class U>
	typename vector_iterator<T>::difference_type	operator-(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter1.base() - Iter2.base()); }


	/* vector container redefinition */

	template<class T , class Allocator = std::allocator<T> >
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
			vector(typename ft::enable_if< !ft::is_integral<InputIt>::value ,InputIt>::type first, InputIt last, const Allocator &alloc = Allocator()) : _end_cap(NULL, alloc) {
				_begin = _end = _end_cap.second.allocate(std::distance(first, last));
				_end_cap.first = _begin + (std::distance(first, last));
				insert(begin(), first, last);
			}
			vector(const vector &other) : _end_cap(NULL, other.get_allocator()) {
				_begin = _end =_end_cap.second.allocate(other.capacity());
				_end_cap.first = _begin + other.capacity();
				insert(begin(), other.begin(), other.end());
			}
			/* --------- */

			/* ASSING OPERATOR */

			vector	&operator=(const vector &other) {
				if (this == &other)
					return (*this);
				clear();
				_end_cap.second = other.get_allocator();
				_begin = _end = _end_cap.second.allocate(other.capacity());
				_end_cap.first = _begin + other.capacity();
				insert(begin(), other.begin(), other.end());
				return (*this);
			}
			/* --------- */

			void	assign(size_type count, const T &value) {
				for (size_type i = 0; i < count; i++) {
					_end_cap.second.destroy(_begin + i);
					_end_cap.second.construct(_begin + i, value);
				}
			}
			template<class InputIt>
			void	assign(typename ft::enable_if< !ft::is_integral<InputIt>::value ,InputIt>::type first, InputIt last) {
				for (size_type i = 0; first != last; first++, i++) {
					_end_cap.second.destroy(_begin + i);
					_end_cap.second.construct(_begin + i, *first);
				}
			}

			allocator_type	get_allocator() const { return (_end_cap.second); }

			reference		at(size_type pos) {
				if (!(pos < size()))
					throw std::out_of_range(NULL);
				return (_begin[pos]);
			}
			const_reference	at(size_type pos) const {
				if (!(pos < size()))
					throw std::out_of_range(NULL);
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

			reverse_iterator		rbegin() { return (reverse_iterator(_end)); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_end)); }
			reverse_iterator		rend() { return (reverse_iterator(_begin)); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(_begin)); }
			/* --------- */

			/* CAPACITY METHODS */

			bool	empty() const { return (_begin == _end); }
			size_type	size() const { return (_end - _begin); }
			size_type	max_size() const { return (_end_cap.second.max_size()); }

			void	reserve(size_type new_cap) {
				if (new_cap < capacity())
					return ;
				if (new_cap > max_size())
					throw	std::length_error(NULL);
				vector	tmp(new_cap, T(), _end_cap.second);
				tmp.clear();
				tmp.insert(tmp.begin(), this->begin(), this->end());
				*this = tmp;
			}

			size_type	capacity() const { return (_end_cap.first - _begin); }
			/* --------- */

			/* MODIFIER METHODS */

			void	clear() { erase(begin(), end()); }

			iterator	insert(iterator pos, const T &value) {
				if (size() == capacity()) {
					difference_type	pos_val = pos.base() - _begin;
					reserve((size() + 1) * 2);
					pos = begin() + pos_val;
				}
				if (pos != end()) {
					T	tmp = *pos;
					for (iterator next = pos + 1; next < end(); next++) {
						ft::swap(*(next), tmp);
						tmp = *(next);
					}
				}
				_end++;
				_end_cap.second.construct(pos.base(), value);
				return (pos);
			}
			void		insert(iterator pos, size_type count, const T &value) {
				if (size() + count < capacity())
					reserve((size() + count) * 2);
				for (size_type i = 0; i < count; i++, pos++)
					insert(pos, value);
			}
			template<class InputIt>
			void		insert(iterator pos, typename ft::enable_if< !ft::is_integral<InputIt>::value ,InputIt>::type first, InputIt last) {
				if (size() + (last - first) < capacity())
					reserve((size() + (last - first)) * 2);
				for (; first != last; first++, pos++)
					insert(pos, *first);
			}

			iterator	erase(iterator pos) {
				if (pos != end())
					_end_cap.second.destroy(pos.base());
				for (iterator next = pos; next + 1 < end(); next++)
					ft::swap(*next, *(next + 1));
				_end--;
				return (pos);
			}
			iterator	erase(iterator first, iterator last) {
				for (; first != last; first++)
					erase(first);
				return (last);
			}

			void	push_back(const T &value) { insert(end(), value); }
			void	pop_back() { erase(end()); }

			void	resize(size_type count, T value = T()) {
				if (count > size())
					insert(end(), count - size(), value);
				else
					for (; size() - count;)
						erase(end() - 1);
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
