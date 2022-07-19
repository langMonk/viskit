///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 30.04.2019
///

#include <exception>
#include <thread>
#include <viskit/parse/ParserCSV.h>

namespace viskit::parse {
namespace {
    template <class T>
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

void ParserCSV::loadFile(const std::string& datasetFilePath, const std::string& labelsFilePath, particles::ParticleSystem& ps)
{
    viskit::DatasetInfo info;

    try {
        info.fileName = remove_extension(base_name(datasetFilePath));
        info.path = base_path(datasetFilePath);

        auto datasetInput = std::ifstream(datasetFilePath.c_str());
        if (!datasetInput.is_open()) {
            throw std::invalid_argument("Could not open the dataset file");
        }
        datasetInput.clear();
        datasetInput.seekg(0, std::ios::beg);
        m_ext_system.logger().logInfo("[CSV Parser] Loading dataset from file: " + datasetFilePath);

        auto labelsInput = std::ifstream(labelsFilePath.c_str());
        if (!labelsInput.is_open()) {
            throw std::invalid_argument("Could not open the labels file");
        }
        labelsInput.clear();
        labelsInput.seekg(0, std::ios::beg);
        m_ext_system.logger().logInfo("[CSV Parser] Loading labels from file: " + labelsFilePath);

        std::string datasetLine;
        std::string labelLine;

        particles::Dataset dataset;
        std::vector<particles::DataPointLabel> labels;

        size_t count = 0;
        size_t dimensionality = 0;

        if (!labelsFilePath.empty()) {
            m_ext_system.logger().logInfo("[CSV Parser] Labels file passed.");

            while (std::getline(datasetInput, datasetLine)) {
                std::getline(labelsInput, labelLine);

                std::vector<std::string> stringVector;
                tokenize(datasetLine, stringVector);

                if (count == 0) {
                    dimensionality = stringVector.size();
                }

                std::vector<float> floatVector(stringVector.size());
                std::transform(stringVector.begin(), stringVector.end(), floatVector.begin(),
                    [&](const std::string& val) {
                        return std::stof(val);
                    });

                particles::DataPointLabel label = std::stoi(labelLine);
                dataset.push_back(std::make_pair(DataPoint(floatVector, count), label));

                if (std::find(labels.begin(), labels.end(), label) == labels.end()) {
                    labels.emplace_back(label);
                }

                count++;
            }
        } else {
            m_ext_system.logger().logInfo("[CSV Parser] No labels file passed.");

            while (std::getline(datasetInput, datasetLine)) {
                std::vector<std::string> stringVector;
                tokenize(datasetLine, stringVector);

                if (count == 0) {
                    dimensionality = stringVector.size();
                }

                std::vector<float> floatVector(stringVector.size());
                std::transform(stringVector.begin(), stringVector.end(), floatVector.begin(),
                    [&](const std::string& val) {
                        return std::stof(val);
                    });

                dataset.push_back(std::make_pair(DataPoint(floatVector, count), 0));

                count++;
            }
        }

        info.count = count;
        info.dimensionality = dimensionality;
        ps.calculationData()->generate(count);

        m_ext_system.logger().logInfo("[CSV Parser] Dataset size: " + std::to_string(info.count));
        m_ext_system.logger().logInfo("[CSV Parser] Dataset dimensionality: " + std::to_string(info.dimensionality));

        if (!labelsFilePath.empty()) {
            m_ext_system.logger().logInfo("[CSV Parser] Number of classes in dataset: " + std::to_string(labels.size()));
        }

        ps.setDataset(dataset, labels);
        ps.datasetInfo(info);
        finalize(ps);

        m_ext_system.logger().logInfo("[CSV Parser] Finished.");

        datasetInput.close();
        labelsInput.close();
    } catch (std::ios_base::failure& e) {
        std::cerr << e.what() << '\n';
        throw std::ios_base::failure(std::string(e.what()));
    }
}

void ParserCSV::tokenize(std::string& str, std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(44, end)) != std::string::npos) {
        end = str.find(44, start);
        out.push_back(str.substr(start, end - start));
    }
}
}