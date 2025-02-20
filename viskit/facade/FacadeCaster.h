///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include <viskit/viskit/ICaster.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/facade/FacadeGraph.h>
#include <viskit/embed/cast/CasterRandom.h>

namespace viskit::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCaster : public virtual ICaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCaster(std::shared_ptr<core::Core> core);
		~FacadeCaster() override = default;

		FacadeCaster(const FacadeCaster&) = delete;
		FacadeCaster(FacadeCaster&&) = delete;

		FacadeCaster& operator=(const FacadeCaster&) = delete;
		FacadeCaster& operator=(FacadeCaster&&) = delete;

		void step(IParticleSystem& ps, IGraph& graph) override;

        void initialize(viskit::IParticleSystem& ps, viskit::IGraph& graph) override {};

        void finalize() override {};

		// protected members
	protected:
		std::shared_ptr<core::Core> m_ext_core;

		std::shared_ptr<embed::cast::Caster> m_internalCaster;
	};
}