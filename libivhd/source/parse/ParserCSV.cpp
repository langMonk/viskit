///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2019
///

#include <boost/algorithm/string.hpp>
#include "parse/ParserCSV.h"

namespace ivhd::parse
{
	namespace
	{
		template<class T>
		T remove_extension(T const& filename)
		{
			typename T::size_type const p(filename.find_last_of('.'));
			return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
		}

		std::string base_name(std::string const& path)
		{
			return path.substr(path.find_last_of("/\\") + 1);
		}

		std::string base_path(std::string const& path)
		{
			return path.substr(0, path.find_last_of("/\\") + 1);
		}

	}

	ParserCSV::ParserCSV(core::System& system)
		: Parser(system)
	{

	}

	void ParserCSV::loadFile(std::string filePath, particles::ParticleSystem& ps)
	{
		auto data = ps.calculationData();
		auto input = std::ifstream(filePath.c_str());

		ivhd::DatasetInfo info;
		info.fileName = remove_extension(base_name(filePath));
		info.path = base_path(filePath);

		input.clear();
		input.seekg(0, std::ios::beg);
		if (!input.good())
		{
			m_ext_system.logger().logError("[CSV Parser] Problems while opening the file : " + filePath);
		}
		else
		{
			m_ext_system.logger().logInfo("[CSV Parser] Loading dataset from file: " + filePath);
		}

		bool firstLine = true, secondLine = true;
		std::string line = "";

		particles::Dataset dataset;
		std::vector<particles::DataPointLabel> labels;
					
		size_t i = 0;
		while (std::getline(input, line))
		{
			if (firstLine)
			{
				line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
				line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
				m_ext_system.logger().logInfo("[CSV Parser] Dataset size: " + line);
				auto count = std::stoi(line);
				info.count = count;
				firstLine = false;

				data->generate(count);
			}
			else if (secondLine)
			{
				line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
				line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
				m_ext_system.logger().logInfo("[CSV Parser] Dataset dimensionality: " + line);
				info.dimensionality = std::stoi(line);
				secondLine = false;
			}
			else
			{
				std::vector<std::string> stringVector;
				boost::algorithm::split(stringVector, line, boost::is_any_of(","));

				std::vector<float> floatVector(stringVector.size() - 1);

				std::transform(stringVector.begin(), stringVector.end() - 1, floatVector.begin(), [](const std::string& val)
				{
					return std::stof(val);
				});

				particles::DataPointLabel label = std::stoi(stringVector.back());
				dataset.push_back(std::make_pair(DataPoint(floatVector, i), label));

				if (std::find(labels.begin(), labels.end(), label) == labels.end())
				{
					labels.emplace_back(label);
				}
				i++;
			}			
		}

		ps.setDataset(dataset, labels);
		ps.datasetInfo(info);
		finalize(ps);

		m_ext_system.logger().logInfo("[CSV Parser] Finished.");

		input.close();
	}
}
