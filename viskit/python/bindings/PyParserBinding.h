//
// \author Radosław Szuma <szuma@student.agh.edu.pl>
// \date 17.05.2022
//

#include "viskit/viskit/IParser.h"

namespace viskit::python::bindings {
class PyParserBinding : public IParser {
public:
    using IParser::IParser;

    void loadFile(std::string datasetFilePath, std::string labelsFilePath, IParticleSystem& ps) override;

    void static bind(pybind11::module& m);
};
}
