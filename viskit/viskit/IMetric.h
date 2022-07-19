///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 17.06.2020
///

#pragma once

namespace viskit {
class IParticleSystem;

class IMetric {
public:
    virtual float calculate(viskit::IParticleSystem& ps, int k) = 0;
};
}