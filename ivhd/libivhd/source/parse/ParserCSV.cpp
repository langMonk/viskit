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

	void ParserCSV::loadFile(std::string filePath, particles::ParticleSystem& ps)
	{	
		auto data = ps.calculationData();
		auto input = std::ifstream(filePath.c_str());

		// count+1, because the last line of csv file won't contain '\n'
		auto count = std::count(std::istreambuf_iterator<char>(input),
			std::istreambuf_iterator<char>(), '\n')+1;

		m_ext_system.logger().logInfo("Loaded dataset with  " + std::to_string(count) + " points was loaded.");
		data->generate(count);

		input.clear();
		input.seekg(0, std::ios::beg);
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

		particles::Dataset dataset;
		std::vector<particles::DataPointLabel> labels;
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

			particles::DataPointLabel label = std::stoi(stringVector.back());
			dataset.push_back(std::make_pair(DataPoint(floatVector), label));

			if (std::find(labels.begin(), labels.end(), label) == labels.end())
			{
				labels.emplace_back(label);
			}
		}

		ps.setDataset(dataset, labels);
		finalize(ps);
		input.close();
	}
}
