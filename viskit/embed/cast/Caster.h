///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <viskit/core/System.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::embed::cast {
class Caster {
    // public construction and destruction methods
public:
    explicit Caster(const core::System& system);
    virtual ~Caster() = default;

    Caster(const Caster&) = delete;
    Caster& operator=(const Caster&) = delete;

    virtual void castParticleSystem(particles::ParticleSystem& ps, Graph& graph) {};

    virtual void calculatePositions(particles::ParticleSystem& ps) {};

protected:
    const core::System& m_ext_system;
};
}