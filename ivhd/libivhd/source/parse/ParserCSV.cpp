///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2019
///

#include <boost/algorithm/string.hpp>

#include "parse/ParserCSV.h"

namespace ivhd::parse
{ 
	ParserCSV::ParserCSV(core::ParticleSystem& system)
		: m_ext_system(system)
	{

	}

	void ParserCSV::initialize(std::string filePath)
	{
		m_input = std::ifstream(filePath.c_str());

		if (!m_input.good())
		{
			m_ext_system.logger().logError("Problems while opening the file : " + filePath);
		}

		std::string line = "";
		std::getline(m_input, line);
		
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(","));

		m_ext_system.logger().logInfo("Loading data from file: " + filePath + ". Data dimensionality: " + std::to_string(vec.size() - 1));
		m_input.close();
	}

	void ParserCSV::loadFile(std::string filePath)
	{
		initialize(filePath);
		
		auto input = std::ifstream(filePath.c_str());

		size_t idx = 0;
		std::string line = "";

		// Iterate through each line and split the content using delimeter
		while (std::getline(input, line))
		{
			std::vector<std::string> vec;
			boost::algorithm::split(vec, line, boost::is_any_of(","));
			m_coordinates.push_back(vec);
		}


		std::ofstream myfile;
		myfile.open("coords.txt");
		for (auto vec : m_coordinates)
		{
			for (std::string data : vec)
			{
				myfile << data << " , ";
			}
			myfile << std::endl;
		}

		finalize(input);
	}

	void ParserCSV::finalize(std::ifstream& input)
	{
		input.close();
		/*if (!input.good())
		{
			m_logger.logError("Cannot close the File");
		}*/
	}
}
