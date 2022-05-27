///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <viskit/facade/FacadeParserCSV.h>

namespace viskit::facade {
FacadeParserCSV::FacadeParserCSV(const std::shared_ptr<core::Core>& core)
    : FacadeParser(core)
    , m_internalParser(std::make_shared<viskit::parse::ParserCSV>(core->system()))
{
}

void FacadeParserCSV::loadFile(const std::string datasetFilePath, const std::string labelsFilePath, IParticleSystem& ps)
{
    try {
        const auto facadePs = reinterpret_cast<FacadeParticleSystem*>(&ps);
        m_internalParser->loadFile(datasetFilePath, labelsFilePath, facadePs->internalSystem());
    } catch (std::exception& ex) {
        m_ext_core->logger().logWarning("Failed to load data file: " + datasetFilePath + ". Error message: " + ex.what());
        throw std::ios_base::failure("Error: " + std::string(ex.what()));
    }
}
}
