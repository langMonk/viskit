#pragma once

#include <memory>
#include <functional>
#include <ivhd/Math.h>
#include <ivhd/Structures.h>

namespace ivhd
{
    class ICaster;
    class IInteractiveVisualization;
    class IGraphGenerator;
}

namespace ivhd {
    namespace cuda {
        class IGpuFactory {
        public:
            static std::unique_ptr<IGpuFactory> create();

        public:
            virtual std::shared_ptr<ivhd::ICaster>
            createCaster(ivhd::CasterType type, ivhd::OptimizerType optimizer) = 0;

            virtual std::shared_ptr<ivhd::IGraphGenerator> createGraphGenerator(ivhd::GraphGeneratorType type) = 0;
        };
    }
}