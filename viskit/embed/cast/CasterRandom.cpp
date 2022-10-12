///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <viskit/embed/cast/CasterRandom.h>

namespace viskit::embed::cast {
CasterRandom::CasterRandom(const core::System& system)
    : Caster(system)
{
}

void CasterRandom::calculatePositions(particles::ParticleSystem& ps)
{
    auto& positions = ps.calculationData()->m_pos;

    for (auto i = 0; i < ps.countParticles(); i++) {
        positions[i].x = static_cast<float>(m_gen->gen());
        positions[i].y = static_cast<float>(m_gen->gen());
    }
}
}