//
// Created by Bartosz Minch on 02/05/2022.
//

#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;

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

            py::enum_<viskit::OptimizerType>(m, "OptimizerType")
                    .value("None", viskit::OptimizerType::None)
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
        }
    };
}