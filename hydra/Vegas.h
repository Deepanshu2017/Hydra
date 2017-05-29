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
 * Vegas.h
 *
 *  Created on: 19/07/2016
 *      Author: Antonio Augusto Alves Junior
 */

/**
 * \file
 * \ingroup numerical_integration
 */

#ifndef VEGAS_H_
#define VEGAS_H_

#include <iostream>

#include <hydra/detail/Config.h>
#include <hydra/detail/BackendPolicy.h>
#include <hydra/Types.h>
#include <hydra/VegasState.h>
#include <hydra/detail/functors/ProcessCallsVegas.h>
#include <hydra/detail/Integrator.h>


namespace hydra {

template<size_t N, typename  BACKEND,  typename GRND=thrust::random::default_random_engine >
class Vegas ;

template<size_t N,  hydra::detail::Backend  BACKEND,  typename GRND>
class Vegas<N, hydra::detail::BackendPolicy<BACKEND>, GRND >
: public Integrator<Vegas<N,hydra::detail::BackendPolicy<BACKEND>,GRND>>
{
	std
	typedef typename system_t::template container<GReal_t>  rvector_backend;
	typedef typename system_t::template container<GUInt_t>  uvector_backend;

	typedef typename rvector_backend::iterator rvector_iterator;
	typedef typename uvector_backend::iterator uvector_iterator;


public:

	//tag
	typedef void hydra_integrator_tag;


	Vegas()=delete;

	Vegas(std::array<GReal_t,N> const& xlower,	std::array<GReal_t,N> const& xupper, size_t ncalls):
		Integrator<Vegas<N, hydra::detail::BackendPolicy<BACKEND>,GRND>>(),
		fState(xlower,xupper)
		{
		fState.SetCalls(ncalls);
		}


		Vegas(VegasState<N, hydra::detail::BackendPolicy<BACKEND>> const& state):
		Integrator<Vegas<N, hydra::detail::BackendPolicy<BACKEND>,GRND>>(),
		fState(state)
		{}


	template< hydra::detail::Backend  BACKEND2, typename GRND2>
	Vegas( Vegas< N, hydra::detail::BackendPolicy<BACKEND2>, GRND2> const& other):
	Integrator<Vegas<N, hydra::detail::BackendPolicy<BACKEND>,GRND>>(),
	fState(other.GetState())
	{}


	void PrintLimits()  ;
	void PrintHead()   ;
	void PrintDistribution()  ;
	void PrintGrid()  ;

	void PrintResults(GReal_t integral, GReal_t sigma,
			GReal_t cumulated_integral, GReal_t cumulated_sigma,
			GReal_t time) ;

	VegasState<N,hydra::detail::BackendPolicy<BACKEND>>& GetState()  {
		return fState;
	}

	VegasState<N,hydra::detail::BackendPolicy<BACKEND>> const& GetState() const {
			return fState;
		}

	void SetState(VegasState<N,hydra::detail::BackendPolicy<BACKEND>> const& state) {
		fState = state;
	}

	template<typename FUNCTOR>
	std::pair<GReal_t, GReal_t> Integrate(FUNCTOR const& functor) ;

private:



	template<typename FUNCTOR>
	std::pair<GReal_t, GReal_t> IntegIterator(FUNCTOR const& functor, GBool_t training);

	void InitGrid();
	void ResetGridValues();
	void InitBoxCoordinates();

	void ResizeGrid(const GInt_t bins);
	void RefineGrid();

	template<typename FUNCTOR>
	void ProcessFuncionCalls(FUNCTOR const& functor, GBool_t training,GReal_t& integral, GReal_t& tss);


	inline GReal_t GetCoordinate(const GUInt_t i, const GUInt_t j) const {
		return fState.GetXi()[i * N + j];
	}

	inline void SetCoordinate(const GUInt_t i, const GUInt_t j, const GReal_t x) {
		fState.SetXi(i * N + j, x);
	}

	inline GReal_t GetNewCoordinate(const GUInt_t i) const {
		return fState.GetXin()[i];
	}

	inline void SetNewCoordinate(const GUInt_t i, const GReal_t x) {
		fState.SetXin(i, x);
	}

	inline GReal_t GetDistributionValue(const GUInt_t i, const GUInt_t j) const {
		return fState.GetDistribution()[i * N + j];
	}

	inline void SetDistributionValue(const GUInt_t i, const GUInt_t j,
			const GReal_t x) {
		fState.SetDistribution(i * N + j, x);
	}

	VegasState<N,hydra::detail::BackendPolicy<BACKEND>> fState;
	rvector_backend fFValInput;
	uvector_backend fGlobalBinInput;
	rvector_backend fFValOutput;
	uvector_backend fGlobalBinOutput;
};

}

#include <hydra/detail/Vegas.inl>
#endif /* VEGAS_H_ */
