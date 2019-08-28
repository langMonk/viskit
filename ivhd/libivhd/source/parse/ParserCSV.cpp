///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2019
///

#include <boost/algorithm/string.hpp>
#include "parse/ParserCSV.h"

namespace ivhd::parse
{ 
	ParserCSV::ParserCSV(core::System& system) 
		: Parser(system)
	{

	}

	void ParserCSV::loadFile(std::string filePath, size_t maxSize, particles::ParticleSystem& ps)
	{	
		auto data = ps.calculationData();
		data->generate(maxSize);

		auto input = std::ifstream(filePath.c_str());

		if (!input.good())
		{
			m_ext_system.logger().logError("Problems while opening the file : " + filePath);
		}
		else 
		{ 
			m_ext_system.logger().logInfo("Loading data from file: " + filePath);
		}
		
		bool firstLine = true;
		std::string line = "";

		while (std::getline(input, line))
		{
			std::vector<std::string> stringVector;
			boost::algorithm::split(stringVector, line, boost::is_any_of(","));

			if (firstLine) 
			{
				m_ext_system.logger().logInfo("Data dimensionality: " + std::to_string(stringVector.size() - 1));
				firstLine = false;
			}

			std::vector<float> floatVector(stringVector.size()-1);

			std::transform(stringVector.begin(), stringVector.end()-1, floatVector.begin(), [](const std::string& val)
			{
				return std::stof(val);
			});

			size_t label = std::stoi(stringVector.back());

			ps.originalCoordinates().push_back(std::make_pair(graph::Point(floatVector), label));
		}

		finalize(ps);
		input.close();
	}
}
