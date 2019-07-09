///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include "core/System.h"

namespace ivhd::graph
{
	class GraphGenerator 
	{
		// public construction and destruction methods
	public:

		GraphGenerator(core::System& system, bool useCache);

		// public methods
	public:
		void kNN();

		// private members
	private:
		core::System& m_ext_system;

		bool m_useCache;
	};
}