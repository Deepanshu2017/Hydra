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
 * DEVICE.h
 *
 *  Created on: 16/05/2017
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef DEVICE_H_
#define DEVICE_H_


#include <hydra/detail/Config.h>
#include <hydra/detail/BackendPolicy.h>
#include <thrust/execution_policy.h>
#include <hydra/Containers.h>

namespace hydra {

namespace detail {

namespace device {

typedef thrust::detail::device_t	            device_t;
static const device_t   _device_;

}  // namespace device

template<>
struct BackendPolicy<Backend::Device>: thrust::execution_policy<device::device_t>
{
	const device::device_t backend= _device_;
	template<typename T>
	using   container = hydra::mc_device_vector<T>;
};


}  // namespace detail

namespace device {

typedef hydra::detail::BackendPolicy<hydra::detail::Backend::Device> sys_t;
static const sys_t sys;

}  // namespace device

}  // namespace hydra



#endif /* DEVICE_H_ */