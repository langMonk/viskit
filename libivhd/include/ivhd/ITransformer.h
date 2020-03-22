///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <map>
#include <iostream> 
#include "ISetting.h"

namespace ivhd
{ 
	/// <summary>
	/// The public interface to objects, which will be able to transform between spaces.
	/// </summary>
	class ITransformer
	{
		// public methods
	public:
		/// <summary>
		/// Reset all the settings associated with this ITransformer.
		/// </summary>
		virtual void resetSettings() = 0;

		/// <summary>
		/// Load settings to this object.
		/// </summary>
		virtual void loadSettings(std::istream& in) = 0;

		/// <summary>
		/// Save settings currently associated with this object.
		/// </summary>
		virtual void saveSettings(std::ostream& out) = 0;

		// protected construction and destruction methods
	protected:

		virtual ~ITransformer() = default;
	};
}