/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2016 Antonio Augusto Alves Junior
 *
 *   This file is part of Hydra Data Analysis Framework.
 *
 *   Hydra is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hydra is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hydra.  If not, see <http://www.gnu.org/licenses/>.
 *
 *---------------------------------------------------------------------------*/

/*
 * next_permutation.h
 *
 *  Created on: Mar 27, 2017
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef NEXT_PERMUTATION_H_
#define NEXT_PERMUTATION_H_



#include <hydra/detail/Config.h>
#include <thrust/sort.h>
#include <thrust/memory.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/swap.h>
#include <thrust/reverse.h>

namespace hydra {

namespace detail {

template <class Iterator>
__host__ __device__
void iter_swap(Iterator first, Iterator second)
{	thrust::swap(*thrust::raw_pointer_cast(first), *thrust::raw_pointer_cast(second)); }

template <class Iterator>
__host__ __device__
Iterator rotate(Iterator first, Iterator n_first, Iterator last)
{

	using hydra::detail::iter_swap;

	if(first == n_first) return last;
	if(n_first == last) return first;

	Iterator next = n_first;

	do {
		iter_swap(first++, next++);
		if (first == n_first) n_first = next;
	}
	while (next != last);

	Iterator ret = first;

	for(next = n_first; next != last; ) {
		iter_swap( first++, next++);
		if(first == n_first) n_first = next;
		else if(next == last) next = n_first;
	}

	return ret;
}

template<typename Iterator, typename Integer, typename Comparator>
typename std::enable_if<std::is_integral<Integer>::value, void>::type
__host__ __device__
nth_permutation(Iterator begin, Iterator end, Integer n, Comparator comp)
{
	thrust::sort(begin, end, comp);

	const Integer k(end - begin);

	Integer radix = Integer(1);
	for(Integer i = Integer(2); i < k; ++i)
		radix *= i;

	for(Integer i = 0; i < k; ++i)
	{

		Integer digit = n / radix;
		rotate(begin, begin + digit, begin + digit + 1);
		++ begin;
		n %= radix;
		if (i + 1 != k)
			radix /= (k - i - 1);
	}
}

/*
 * similar
 */

template<class BidirIt>
__host__ __device__
bool next_permutation(BidirIt first, BidirIt last)
{
	if (first == last) return false;
	BidirIt i = last;
	if (first == --i) return false;

	while (true) {
		BidirIt i1, i2;

		i1 = i;
		if (*--i < *i1) {
			i2 = last;
			while (!(*i < *--i2))
				;
			hydra::iter_swap(i, i2);
			thrust::reverse(i1, last);
			return true;
		}
		if (i == first) {
			thrust::reverse(first, last);
			return false;
		}
	}
}

}  // namespace detail

} // namespace hydra

#endif /* NEXT_PERMUTATION_H_ */
