#pragma once

#include <memory>

#include "IInteractiveVizualization.h"

namespace ivhd
{
	/// <summary>
	/// Creates the IVHD.
	/// </summary>
	/// <returns>The created IVHD resource or nullptr in case of an error.</returns>
	std::shared_ptr<IInteractiveVizualization> createIVHD();
}