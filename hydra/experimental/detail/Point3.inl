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
 * Point3.inl
 *
 *  Created on: 16/02/2017
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef POINT3_INL_
#define POINT3_INL_


#include <hydra/detail/Config.h>
#include <hydra/Types.h>
#include <hydra/detail/utility/Utility_Tuple.h>

#include <hydra/detail/utility/Arithmetic_Tuple.h>
//std
#include <array>

//thrust
#include <thrust/tuple.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

namespace hydra {

namespace experimental {


template<typename T, size_t DIM>
struct Point<T, DIM, true, true>
{
	constexpr static size_t N = 2*DIM + 3;
	constexpr static const size_t Dimension=DIM;

	typedef typename hydra::detail::tuple_type<N, T>::type type;
	typedef typename hydra::detail::tuple_type<DIM, T>::type coordinate_type;
	typedef  T value_type;

	/**
	 * Default constructor for points
	 * without errors in coordinates and value
	 */
	__host__ __device__
	Point():
	fData()
	{ }

	/**
	 * Trivial constructor for points
	 * without errors in coordinates and value
	 */
	__host__ __device__
	Point(type const& data):
	fData(data)
	{ }


	/**
	 * Constructor for points without errors in coordinates and value
	 * @param coordinates:  std::array<value_type,DIM> with the coordinates
	 * @param weight: weight of this point
	 */
	__host__
	Point(std::array<value_type,DIM> const& coordinates,
			std::array<value_type,DIM> const& coordinate_errors, value_type error=0.0, value_type weight=1.0 )
	{
		auto weights = thrust::make_tuple(weight, weight*weight, error );
		auto coords  = hydra::detail::arrayToTuple<value_type,DIM>(const_cast<value_type*>(coordinates.data() ));
		auto coords_errors  = hydra::detail::arrayToTuple<value_type,DIM>(const_cast<value_type*>(coordinates_errors.data() ));
		fData = thrust::tuple_cat(weights, coords  );
	}

	/**
	 * Constructor for points without errors in coordinates and value
	 * @param coordinates: value_type[DIM] with the coordinates
	 * @param weight: weight of this point
	 */
	__host__ __device__
	Point(value_type (&coordinates)[DIM],
			value_type (&coordinates_errors)[DIM], value_type error=0.0 ,  value_type weight=1.0)
	{
		auto weights = thrust::make_tuple(weight, weight*weight, error );
		auto coords  = hydra::detail::arrayToTuple<value_type,DIM>(const_cast<value_type*>( &coordinates[0] ));
		auto coords_errors  = hydra::detail::arrayToTuple<value_type,DIM>(const_cast<value_type*>( &coordinates_errors[0] ));
		fData = thrust::tuple_cat(weights, coords  );
	}

	/**
	 * Constructor for points without errors in coordinates and value
	 * @param coordinates: std::initializer_list
	 * @param weight: weight of this point
	 */
	__host__
	Point(std::initializer_list<value_type> coordinates,
			std::initializer_list<value_type> coordinates_errors, value_type error=0.0, value_type weight=1.0 )
	{
		std::vector<value_type> v(coordinates);
		std::vector<value_type> ve(coordinates_errors);
		auto weights = thrust::make_tuple(weight, weight*weight, error  );
		auto coords  = hydra::detail::arrayToTuple<value_type,DIM>(const_cast<value_type*>(v.data() ));
		auto coords_errors  = hydra::detail::arrayToTuple<value_type,DIM>(const_cast<value_type*>(ve.data() ));
		fData = thrust::tuple_cat(weights, coords  );
	}


	/**
	 * Constructor for points without errors in coordinates and value
	 * @param coordinates: std::initializer_list
	 * @param weight: weight of this point
	 * @return
	 */
	__host__  __device__
	Point(  coordinate_type coordinates,
			coordinate_type coordinates_errors, value_type error=0.0, value_type weight=1.0)
	{
		auto weights = thrust::make_tuple(weight, weight*weight, error );
		fData = thrust::tuple_cat(weights, coordinates  );
	}

	/**
	 * Constructor for points without errors in coordinates and value
	 * @param coordinates: pointer to array dimension DIM
	 * @param weight: weight of this point
	 * @return
	 */
	__host__  __device__
	explicit Point(value_type* coordinates,
			value_type* coordinates_errors, value_type error=0.0,	value_type weight=1.0 )
	{
		auto weights = thrust::make_tuple(weight, weight*weight, error  );
		auto coords  = hydra::detail::arrayToTuple<value_type,DIM>(const_cast<value_type*>( coordinates));
		fData = thrust::tuple_cat(weights, coords  );
	}


	__host__  __device__
	Point( Point<value_type,DIM, true, true> const& other):
	fData(other.GetData() )
	{}

	__host__  __device__ inline
	Point<value_type,DIM, true, true>& operator=( Point<value_type,DIM, true, true> const& other)
	{
		if( this == &other) return *this;

		fData=other.GetData() ;

		return *this;
	}

	__host__  __device__ inline
	Point<value_type,DIM, true, true>& operator=(type const& other)
	{
		if( this == &other) return *this;

		fData=other ;

		return *this;
	}


	__host__  __device__
	inline void SetCoordinate(coordinate_type const& coordinates,
			coordinate_type const& coordinates_errors=coordinate_type(), value_type error=0.0,
			value_type weight=1.0) const{

		auto weights = thrust::make_tuple(weight, weight*weight );
		fData = thrust::tuple_cat(weights, coordinates  );

	}

	__host__  __device__
	inline auto GetCoordinates()
	-> decltype( hydra::detail::split_tuple<3>(type()).second )
	{

		return hydra::detail::split_tuple<3>(fData).second;
	}

	__host__  __device__
	inline auto GetCoordinates() const
	-> const decltype( hydra::detail::split_tuple<3>(type()).second )
	{

		return hydra::detail::split_tuple<3>(fData).second;
	}


	__host__  __device__
	inline value_type GetCoordinate(const int i) const{
		return hydra::detail::extract<value_type, type>(i+3, fData);
	}


	__host__  __device__
	inline void SetData(type data) {
		fData = data;
	}

	__host__  __device__
	inline type& GetData() {
			return fData;
		}

	__host__  __device__
	inline type const& GetData() const {
		return fData;
	}

	__host__  __device__
	inline value_type GetError() {

		return thrust::get<2>(fData);
	}

	__host__  __device__
	inline const value_type GetError() const {
		return thrust::get<2>(fData);
	}

	__host__  __device__
	inline void SetError(value_type weight) {
		thrust::get<2>(fData) = weight;
	}

	__host__  __device__
	inline value_type GetWeight() {

		return thrust::get<0>(fData);
	}

	__host__  __device__
	inline const value_type GetWeight() const {
		return fWeight;
	}

	__host__  __device__
	inline void SetWeight(value_type weight) {
		thrust::get<0>(fData) = weight;
	}

	__host__  __device__
	inline value_type GetWeight2()  {
		return thrust::get<1>(fData);
	}

	__host__  __device__
	inline value_type GetWeight2() const {
		return thrust::get<1>(fData);
	}

	__host__  __device__
	inline void SetWeight2(value_type weight2) {
		thrust::get<1>(fData) = weight2;
	}



	operator type() const { return fData; }
	operator type() { return fData; }

private:
	type fData;
};

}  // namespace experimental

} // namespace hydra




#endif /* POINT3_INL_ */