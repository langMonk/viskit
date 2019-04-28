#include "parse\ParserCSV.h"

namespace ivhd::parse
{ 
	ParserCSV::ParserCSV(core::ParticleSystem& system, core::Logger& logger)
		: m_system(system)
		, m_logger(logger)
	{

	}

	void ParserCSV::initialize(std::string filePath)
	{
		m_input = std::ifstream(filePath.c_str());

		if (!m_input.good())
		{
			m_system.logger().logError("Problems while opening the file : " + filePath);
		}

		std::string str;
		std::getline(m_input, str, ',');

		m_input.close();
	}

	void ParserCSV::loadFile(std::string filePath)
	{
		initialize(filePath);
		
		auto input = std::ifstream(filePath.c_str());

		size_t idx = 0;
		std::string str;
		while (std::getline(m_input, str, ','))
		{
			std::cout << str << std::endl;
		}

		finalize(input);
	}

	void ParserCSV::finalize(std::ifstream& input)
	{
		input.close();
		if (input.good())
		{
			m_system.logger().logError("Cannot close the File");
		}
	}
}
