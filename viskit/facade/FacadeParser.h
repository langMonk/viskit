///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 12.05.2019
///

#pragma once

#include <viskit/embed/cast/CasterRandom.h>
#include <viskit/facade/FacadeParticleSystem.h>
#include <viskit/viskit/IParser.h>
#include <viskit/viskit/IParticleSystem.h>

namespace viskit::facade {
/// <summary>
/// Implementation of IParser interface.
/// </summary>
class FacadeParser : public virtual IParser {
    // public construction and destruction methods
public:
    explicit FacadeParser(std::shared_ptr<core::Core> core);
    ~FacadeParser() = default;

    FacadeParser(const FacadeParser&) = delete;
    FacadeParser(FacadeParser&&) = delete;

    FacadeParser& operator=(const FacadeParser&) = delete;
    FacadeParser& operator=(FacadeParser&&) = delete;

    // protected members
protected:
    std::shared_ptr<core::Core> m_ext_core;
};
}