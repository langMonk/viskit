#include "embed/cast/ivhd/CasterTSNE.h"
#include "glm/glm/gtx/norm.hpp"

namespace viskit::embed::cast::ivhd
{
	CasterTSNE::CasterTSNE(core::System& system)
		: CasterIVHD(system)
	{

	}

    void CasterTSNE::calculateForces(float &energy, particles::ParticleSystem &ps, Graph &graph) {
	    const size_t N = ps.countParticles();

        ps.resetForces();
	    auto& positions = ps.calculationData()->m_pos;
	    auto& forces = ps.calculationData()->m_force;

        std::vector<float> lengthsSquared(N);
	    std::transform(positions.begin(), positions.end(), lengthsSquared.begin(), [](glm::vec4 x){ return glm::length2(glm::vec3(x)); });

	    std::vector<std::vector<float>> numerator(N, std::vector(N, .0f));
	    for (int i = 0; i < N; ++i) {
	        for (int j = 0; j < N; ++j) {
	            if (i != j) {
                    numerator[i][j] = 1.0f / (1.0f - 2.0f * glm::dot(glm::vec3(positions[i]), glm::vec3(positions[j])) + lengthsSquared[i] + lengthsSquared[j]);
	            }
	        }
	    }

	    auto denominator = std::accumulate(numerator.begin(), numerator.end(), 0.0f, [](float sum, const std::vector<float>& x){
	        return sum + std::accumulate(x.begin(), x.end(), 0.0f);
	    });

        std::vector<std::vector<float>> negQ(N, std::vector(N, .0f));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) {
                    negQ[i][j] = - numerator[i][j] / denominator;
                }
            }
        }

        float sumP = 0;
        for (int i = 0; i < N; ++i) {
            const auto& neighbours = graph.getNeighbors(i);
            sumP += std::accumulate(neighbours->begin(), neighbours->end(), 0.0f, [](float sum, const auto& x){return sum + x.r;});
        }

        for (int i = 0; i < N; i++) {
            auto& deltaPQ = negQ[i];
            const auto& neighbours = graph.getNeighbors(i);
            for (const auto& neigh : *neighbours) {
                deltaPQ[neigh.j] += neigh.r / sumP;
            }

            for (int j = 0; j < N; ++j) {
                forces[i] += deltaPQ[j] * numerator[i][j] * (positions[i] - positions[j]);
            }
        }
    }

	void CasterTSNE::calculatePositions(particles::ParticleSystem &ps) {
        auto& positions = ps.calculationData()->m_pos;
        auto& forces = ps.calculationData()->m_force;

        iY.resize(ps.countParticles(), glm::vec4{ 0.0f });
        gains.resize(ps.countParticles(), glm::vec4{ 1.0f });

        for (int i = 0; i < ps.countParticles(); ++i) {
            auto cond = glm::equal(glm::greaterThan(forces[i], glm::vec4{ 0.0f }), glm::greaterThan(iY[i], glm::vec4{ 0.0f }));
            gains[i].x = cond.x ? gains[i].x * .8f : gains[i].x + .2f;
            gains[i].y = cond.y ? gains[i].y * .8f : gains[i].y + .2f;

            gains[i] = glm::max(gains[i], MIN_GAIN);

            iY[i] = MOMENTUM * iY[i] - LEARNING_RATE * gains[i] * forces[i];
            positions[i] += iY[i];
        }

        auto meanPos = std::accumulate(positions.begin(), positions.end(), glm::vec4{ 0.0f }) / (float) ps.countParticles();
        std::transform(positions.begin(), positions.end(), positions.begin(), [&meanPos](auto x){return x - meanPos;});
        ps.increaseStep();
	}
}