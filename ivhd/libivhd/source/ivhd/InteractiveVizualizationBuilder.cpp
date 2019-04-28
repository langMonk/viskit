///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 28.04.2019
///

#include "ivhd/InteractiveVizualizationBuilder.h"
#include "facade/FacadeInteractiveVizualization.h"

namespace ivhd
{ 
	std::shared_ptr<IInteractiveVizualization> createIVHD()
	{
		return std::make_shared<facade::FacadeInteractiveVizualization>();
	}
}
