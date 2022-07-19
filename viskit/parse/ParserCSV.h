///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 24.04.2019
///

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <viskit/core/System.h>
#include <viskit/parse/Parser.h>
#include <viskit/particles/ParticleSystem.h>

namespace viskit::parse {
class ParserCSV : public Parser {
    // public construction and destruction methods
public:
    explicit ParserCSV(core::System& system);

    // public methods
public:
    void loadFile(const std::string& datasetFilePath, const std::string& labelsFilePath, particles::ParticleSystem& ps);

private:
    static void tokenize(std::string& str, std::vector<std::string>& out);
};
}