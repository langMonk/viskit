//
// \author Dawid Dębowski <ddebowsk@student.agh.edu.pl>
// \date 21.05.2022.
//

#include "viskit/viskit/DataPoint.h"
#include <pybind11/pybind11.h>

namespace viskit::python::bindings {
class PyDataPointBinding {
public:
    void static bind(pybind11::module& m);
};
}