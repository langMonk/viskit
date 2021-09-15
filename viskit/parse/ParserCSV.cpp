///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2019
///

#include <viskit/parse/ParserCSV.h>
#include <thread>

namespace viskit::parse
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

	void ParserCSV::loadFile(const std::string& filePath, particles::ParticleSystem& ps)
	{
		auto input = std::ifstream(filePath.c_str());

		viskit::DatasetInfo info;
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

		std::string line;

		particles::Dataset dataset;
		std::vector<particles::DataPointLabel> labels;
					
		size_t count = 0;
        size_t dimensionality = 0;

        while (std::getline(input, line))
		{
            std::vector<std::string> stringVector;
            tokenize(line, ',', stringVector);

            if (count == 0) { dimensionality = stringVector.size() - 1; }

            std::vector<float> floatVector(stringVector.size() - 1);
            std::transform(stringVector.begin(), stringVector.end() - 1, floatVector.begin(), [&](const std::string& val)
            {
                return std::stof(val);
            });

            particles::DataPointLabel label = std::stoi(stringVector.back());
            dataset.push_back(std::make_pair(DataPoint(floatVector, count), label));

            if (std::find(labels.begin(), labels.end(), label) == labels.end())
            {
                labels.emplace_back(label);
            }

            count++;
        }

        ps.calculationData()->generate(count);

        info.dimensionality = dimensionality;
        info.count = count;

        m_ext_system.logger().logInfo("[CSV Parser] Dataset size: " + std::to_string(info.count));
        m_ext_system.logger().logInfo("[CSV Parser] Dataset dimensionality: " + std::to_string(info.dimensionality));
        m_ext_system.logger().logInfo("[CSV Parser] Number of classes in dataset: " + std::to_string(labels.size()));

        ps.setDataset(dataset, labels);
		ps.datasetInfo(info);
		finalize(ps);

		m_ext_system.logger().logInfo("[CSV Parser] Finished.");

		input.close();
	}

    void ParserCSV::tokenize(std::string &str, char delim, std::vector<std::string> &out)
    {
        size_t start;
        size_t end = 0;

        while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
        {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }
}