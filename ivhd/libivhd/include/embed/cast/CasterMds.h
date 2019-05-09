///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <map>
#include <iostream>

#include "ivhd/SettingType.h"
#include "Caster.h"

namespace ivhd::embed::cast
{ 
	class CasterMds 
	{
		// public construction and destruction methods
	public:
		CasterMds();

		~CasterMds();


	private:
		std::map<std::string, std::unique_ptr<SettingType>> m_parameters;
	};
}