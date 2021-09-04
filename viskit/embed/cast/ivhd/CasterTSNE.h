///
/// \author Tomasz Załęski
/// \date 25.05.2021
///

#pragma once

#include <viskit/particles/ParticleSystem.h>
#include <viskit/embed/cast/ivhd/CasterIVHD.h>

namespace viskit::embed::cast::ivhd
{
    class CasterTSNE final : public CasterIVHD
    {
        // public construction and destruction methods
    public:
        explicit CasterTSNE(core::System& system);

        // public methods
    public:
        void calculatePositions(particles::ParticleSystem& ps) final;
        void calculateForces(float &energy, particles::ParticleSystem &ps, Graph &graph) final;

    private:
        std::vector<glm::vec4> iY;

        std::vector<glm::vec4> gains;

        float LEARNING_RATE{ 500.f };

        float MOMENTUM{ .5f };

        float MIN_GAIN{ .01f };

    };
}