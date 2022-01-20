///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 15.05.2019
///

#include <viskit/parse/Parser.h>

namespace viskit::parse {
Parser::Parser(core::System& system)
    : m_ext_system(system)
{
}

void Parser::finalize(particles::ParticleSystem& ps)
{
}
}