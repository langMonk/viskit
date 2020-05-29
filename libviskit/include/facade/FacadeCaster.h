///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "ivhd/ICaster.h"
#include "facade/FacadeParticleSystem.h"
#include "facade/FacadeGraph.h"
#include "embed/cast/CasterRandom.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCaster : public virtual ICaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCaster(std::shared_ptr<core::Core> core);
		virtual ~FacadeCaster() = default;

		FacadeCaster(const FacadeCaster&) = delete;
		FacadeCaster(FacadeCaster&&) = delete;

		FacadeCaster& operator=(const FacadeCaster&) = delete;
		FacadeCaster& operator=(FacadeCaster&&) = delete;

		void step(IParticleSystem& ps, IGraph& graph) override;

        void initialize(ivhd::IParticleSystem& ps, ivhd::IGraph& graph) override {};

        void finalize() override {};

		// protected members
	protected:
		std::shared_ptr<core::Core> m_ext_core;

		std::shared_ptr<embed::cast::Caster> m_internalCaster;
	};
}