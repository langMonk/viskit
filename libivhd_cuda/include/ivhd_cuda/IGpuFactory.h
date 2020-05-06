#pragma once

#include <memory>
#include <functional>
#include <Math.h>
#include <Structures.h>

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
            static std::shared_ptr<IGpuFactory> create();

        public:
            virtual std::shared_ptr<ivhd::ICaster> createCaster(ivhd::CasterType type, ivhd::OptimizerType optimizer) = 0;

            virtual std::shared_ptr<ivhd::IGraphGenerator> createGraphGenerator(ivhd::GraphGeneratorType type) = 0;
        };
    }
}