///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.02.2020
///

#include <viskit/embed/cast/ivhd/CasterAdam.h>

namespace viskit::embed::cast::ivhd {
CasterAdam::CasterAdam(const core::System& system)
    : CasterIVHD(system)
{
}

void CasterAdam::calculatePositions(particles::ParticleSystem& ps)
{
    decGrad.resize(ps.countParticles(), glm::vec4 { 0.0f });
    decDelta.resize(ps.countParticles(), glm::vec4 { 0.0f });

    auto& positions = ps.calculationData()->m_pos;
    auto& forces = ps.calculationData()->m_force;

    const auto it = ps.step() + 1;

    for (size_t i = 0; i < ps.countParticles(); i++) {
        decGrad[i].x = decGrad[i].x * B2 + (1.0f - B2) * forces[i].x * forces[i].x;
        decGrad[i].y = decGrad[i].y * B2 + (1.0f - B2) * forces[i].y * forces[i].y;

        decDelta[i].x = decDelta[i].x * B1 + (1.0f - B1) * forces[i].x;
        decDelta[i].y = decDelta[i].y * B1 + (1.0f - B1) * forces[i].y;

        const auto decGradAdjustedx = decGrad[i].x / (1.0f - powf(B2, static_cast<float>(it)));
        const auto decGradAdjustedy = decGrad[i].y / (1.0f - powf(B2, static_cast<float>(it)));

        const auto decDeltaAdjustedx = decDelta[i].x / (1.0f - powf(B1, static_cast<float>(it)));
        const auto decDeltaAdjustedy = decDelta[i].y / (1.0f - powf(B1, static_cast<float>(it)));

        const auto deltax = LEARNING_RATE * decDeltaAdjustedx / (EPS + sqrtf(decGradAdjustedx));
        const auto deltay = LEARNING_RATE * decDeltaAdjustedy / (EPS + sqrtf(decGradAdjustedy));

        positions[i].x += deltax;
        positions[i].y += deltay;
    }

    ps.increaseStep();
}

}
