//
// Created by Bartosz Minch on 02/05/2022.
//

#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;
using namespace py::literals;

namespace viskit::python::bindings
{
    class PyStructuresBinding {
    public:
        void static bind(pybind11::module &m){
            py::enum_<viskit::CasterType>(m, "CasterType")
                    .value("IVHD", viskit::CasterType::IVHD)
                    .value("LargeVis", viskit::CasterType::LargeVis)
                    .value("tSNE", viskit::CasterType::tSNE)
                    .value("Random", viskit::CasterType::Random)
                    .export_values();

            py::enum_<viskit::NeighborsType>(m, "NeighborsType")
                    .value("Near", viskit::NeighborsType::Near)
                    .value("Far", viskit::NeighborsType::Far)
                    .value("Random", viskit::NeighborsType::Random)
                    .value("Reverse", viskit::NeighborsType::Reverse)
                    .value("ToRemove", viskit::NeighborsType::ToRemove)
                    .export_values();

            py::enum_<viskit::OptimizerType>(m, "OptimizerType")
                    .value("NONE", viskit::OptimizerType::None)
                    .value("SGD", viskit::OptimizerType::SGD)
                    .value("ForceDirected", viskit::OptimizerType::ForceDirected)
                    .value("Momentum", viskit::OptimizerType::Momentum)
                    .value("Adadelta", viskit::OptimizerType::Adadelta)
                    .value("Adam", viskit::OptimizerType::Adam)
                    .value("Nesterov", viskit::OptimizerType::Nesterov)
                    .value("tSNE", viskit::OptimizerType::tSNE)
                    .export_values();

            py::enum_<viskit::ParserType>(m, "ParserType")
                    .value("Csv", viskit::ParserType::Csv)
                    .export_values();

            py::enum_<viskit::GraphGeneratorType>(m, "GraphGeneratorType")
                    .value("BruteForce", viskit::GraphGeneratorType::BruteForce)
                    .value("KDTreeBased", viskit::GraphGeneratorType::KDTreeBased)
                    .value("Random", viskit::GraphGeneratorType::Random)
                    .value("Faiss", viskit::GraphGeneratorType::Faiss)
                    .value("Reverse", viskit::GraphGeneratorType::Reverse)
                    .export_values();

            py::enum_<viskit::MetricType>(m, "MetricType")
                    .value("Euclidean", viskit::MetricType::Euclidean)
                    .value("Cosine", viskit::MetricType::Cosine)
                    .export_values();

            py::enum_<viskit::LogLevel>(m, "LogLevel")
                    .value("Debug", viskit::LogLevel::Debug)
                    .value("Info", viskit::LogLevel::Info)
                    .value("Warning", viskit::LogLevel::Warning)
                    .value("Error", viskit::LogLevel::Error)
                    .export_values();

            py::class_<viskit::DatasetInfo>(m, "DatasetInfo")
                    .def(py::init<>())
                    .def_readwrite("path", &viskit::DatasetInfo::path)
                    .def_readwrite("fileName", &viskit::DatasetInfo::fileName)
                    .def_readwrite("count", &viskit::DatasetInfo::count)
                    .def_readwrite("dimensionality", &viskit::DatasetInfo::dimensionality);

            py::class_<viskit::Neighbors>(m, "Neighbors")
                    .def(py::init<>())
                    .def(py::init<size_t, size_t>())
                    .def(py::init<size_t, size_t, float, viskit::NeighborsType>())
                    .def_readwrite("i", &viskit::Neighbors::i)
                    .def_readwrite("j", &viskit::Neighbors::j)
                    .def_readwrite("type", &viskit::Neighbors::type)
                    .def("__eq__", [](const Neighbors &it, Neighbors& rhs) {
                        return it.i == rhs.i && it.j == rhs.j && it.r == rhs.r && it.type == rhs.type;
                    }, py::is_operator());

            py::class_<viskit::NeighborsCounter>(m, "NeighborsCounter")
                    .def(py::init<>())
                    .def_readwrite("nearestNeighbors", &viskit::NeighborsCounter::nearestNeighbors)
                    .def_readwrite("reverseNeighbors", &viskit::NeighborsCounter::reverseNeighbors)
                    .def_readwrite("randomNeighbors", &viskit::NeighborsCounter::randomNeighbors);

            py::class_<viskit::vec4>(m, "Vec4")
                    .def(py::init<float, float, float, float>(), "x"_a=0, "y"_a=0, "z"_a=0, "w"_a=0)
                    .def_readwrite("x", &viskit::vec4::x)
                    .def_readwrite("y", &viskit::vec4::y)
                    .def_readwrite("z", &viskit::vec4::z)
                    .def_readwrite("w", &viskit::vec4::w);
        }
    };
}