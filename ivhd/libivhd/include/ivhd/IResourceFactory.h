///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#pragma once

#include "ivhd/Structures.h"

namespace ivhd
{
	class IParser;
	class ICaster;

	class IResourceFactory
	{
		// public methods
	public:
		/// <summary>
		/// Creates a new parser used for loading data into ivhd
		/// </summary>
		/// <returns>The created parser.</returns>
		virtual std::shared_ptr<IParser> createParser(ParserType type) = 0;

		/// <summary>
		/// Creates a new caster, that might be used for data embedding.
		/// </summary>
		/// <returns>The created caster.</returns>
		virtual std::shared_ptr<ICaster> createCaster(CasterType type) = 0;

	};
}