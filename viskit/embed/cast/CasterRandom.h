///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <viskit/embed/cast/Caster.h>
#include <viskit/particles/ParticleSystem.h>

using Engine = std::mt19937;
using Dist = std::uniform_real_distribution<>;

namespace viskit::embed::cast {
class CasterRandom final : public Caster {
    // public construction and destruction methods
public:
    explicit CasterRandom(const core::System& system);

    // public methods
public:
    void calculatePositions(particles::ParticleSystem& ps) override;

    [[nodiscard]] int maxEdge() const { return m_maxEdge; };

    // Helper structures
private:
    class RandomGenerator {
    public:
        explicit RandomGenerator(float min = -0.5f, float max = 0.5f)
            : m_dist(min, max) {};

        Dist::result_type gen() { return m_dist(m_eng); };

    private:
        Engine m_eng {0};
        Dist m_dist;
    };

    // private members
private:
    int m_maxEdge { 1000 };

    std::shared_ptr<RandomGenerator> m_gen { new RandomGenerator() };
};
}