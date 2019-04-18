///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "ivhd/ICaster.h"

namespace ivhd::cast
{

	class FacadeCasterMDS : public ICaster
	{
		// public construction and destruction methods
	public:
		FacadeCasterMDS();

		// ICaster implementation
	public:
		void cast() override;
		void initialize() override;
		void finalize() override;
		void resetSettings() override;
		void saveSettings(std::ostream& out) override;
		void loadSettings(std::istream& in) override;

	private:

	};
}