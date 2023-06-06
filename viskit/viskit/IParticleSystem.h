///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <libraries/glm/glm/glm.hpp>
#include <vector>
#include <viskit/viskit/DataPoint.h>
#include <viskit/viskit/Math.h>
#include <viskit/viskit/Structures.h>

namespace viskit {
class ICaster;
class IReducer;
class IClusterer;
class IGraph;

class IParticleSystem {
public:
    /// <summary>
    /// Get basic information, that concerns dataset loaded to this particle system.
    /// </summary>
    /// <returns> Dataset information.</returns>
    virtual DatasetInfo datasetInfo() = 0;

    /// <summary>
    /// Returns original coordinates.
    /// </summary>
    /// <returns> Container with data original coordinates.</returns>
    virtual std::vector<std::pair<DataPoint, size_t>> originalCoordinates() = 0;

    /// <summary>
    /// Returns labels associated with this dataset.
    /// </summary>
    /// <returns> Container with current particle labels.</returns>
    virtual std::vector<size_t> labels() = 0;

    /// <summary>
    /// Returns current positions.
    /// </summary>
    /// <returns> Pointer to container with current particles positions.</returns>
    virtual std::vector<viskit::vec4> positions() = 0;

    /// <summary>
    /// Returns current forces.
    /// </summary>
    /// <returns> Pointer to container with current particle forces.</returns>
    virtual std::vector<viskit::vec4> forces() = 0;

    /// <summary>
    /// Returns current velocities.
    /// </summary>
    /// <returns> Pointer to container with current particle velocities.</returns>
    virtual std::vector<viskit::vec4> velocities() = 0;

    /// <summary>
    /// Returns colors associated with each particle.
    /// </summary>
    /// <returns> Pointer to container with colors.</returns>
    virtual std::vector<viskit::vec4> colors() = 0;

    /// <summary>
    /// Sets the specified particle position.
    /// </summary>
    /// <param="index"> Index of particle for which we want to set new coordinates. </param>
    /// <param="x"> X coordinate. </param>
    /// <param="y"> Y coordinate. </param>
    virtual void setPosition(size_t index, float x, float y) = 0;

    /// <summary>
    /// Counts alive particles.
    /// </summary>
    /// <returns> Number of particles, that are currently alive.</returns>
    virtual size_t countAlive() = 0;

    /// <summary>
    /// Count particles.
    /// </summary>
    /// <returns> Number of particles in the system.</returns>
    virtual size_t countParticles() = 0;

    /// <summary>
    /// Clears the particle system (if not empty).
    /// </summary>
    virtual void clear() = 0;

    /// <summary>
    /// Checks if particles system is empty.
    /// </summary>
    /// <returns> True if particle system is empty, false otherwise.</returns>
    virtual bool empty() = 0;

    /// <summary>
    /// Saves a particle system to file.
    /// </summary>
    /// <param name="fileName"> Filename, where ps file should be located.</param>
    /// <returns> True if save operation succeed. </returns>
    virtual bool saveToFile(const std::string& fileName) = 0;

    /// <summary>
    /// Saves a particle system to file.
    /// </summary>
    /// <param name="fileName"> Filename, where ps file should be located.</param>
    /// <param name="graph"> Graph used for saving number of neighbors for each particle.</param>
    /// <returns> True if save operation succeed. </returns>
    virtual bool saveToFile(const std::string& fileName, IGraph& graph) = 0;

    /// <summary>
    /// Loads positions from the file into particle system, when initializing particle system.
    /// Currently supported formats: .npy.
    /// </summary>
    /// <param name="filePath"> Filepath, where data is located.</param>
    virtual void loadParticlesPositions(const std::string& filePath) = 0;

    virtual ~IParticleSystem() = default;
};
}