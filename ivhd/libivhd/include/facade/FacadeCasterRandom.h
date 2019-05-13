///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "ivhd/ICaster.h"
#include "core/ParticleSystem.h"
#include "embed/cast/CasterRandom.h"

namespace ivhd::facade
{
	/// <summary>
	/// Implementation of ICaster interface.
	/// </summary>
	class FacadeCasterRandom : public ICaster
	{
		// public construction and destruction methods
	public:

		explicit FacadeCasterRandom(core::ParticleSystem& system);
		~FacadeCasterRandom() = default;

		FacadeCasterRandom(const FacadeCasterRandom&) = delete;
		FacadeCasterRandom(FacadeCasterRandom&&) = delete;

		FacadeCasterRandom& operator=(const FacadeCasterRandom&) = delete;
		FacadeCasterRandom& operator=(FacadeCasterRandom&&) = delete;

		// public methods
	public:
		void cast() override;

		void initialize() override;

		void finalize() override;

		void resetSettings() override;

		void loadSettings(std::istream& in) override;

		void saveSettings(std::ostream& out) override;

	private:
		ivhd::embed::cast::CasterRandom m_internalCaster;
	};
}