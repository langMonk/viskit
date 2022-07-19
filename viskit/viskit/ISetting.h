///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <functional>
#include <iostream>
#include <viskit/viskit/SettingType.h>

namespace viskit {
/// <summary>
/// The public interface to a particular setting.
/// </summary>
class ISetting {
    // public metods
public:
    /// <summary>
    /// Name associated with this setting
    /// </summary>
    /// <returns>The setting name.</returns>
    virtual std::string name() const = 0;

    /// <summary>
    /// Detailed description of this Setting.
    /// </summary>
    /// <returns>The Setting description.</returns>
    virtual std::string description() const = 0;

    /// <summary>
    /// The type of the Setting, a simple variable like bool or int.<int>
    /// </summary>
    /// <returns>The type of the Setting value.</returns>
    virtual SettingType type() const = 0;

    /// <summary>
    /// Set of values, which are allowed.
    /// </summary>
    /// <returns>The allowed values of the Setting in the string form.</returns>
    virtual std::string allowedValues() const = 0;

    /// <summary>
    /// Returns the default value of the Setting.
    /// </summary>
    /// <returns>The default value of the Setting.</returns>
    virtual std::string defaultValue() const = 0;

    /// <summary>
    /// Returns the current value of the Setting.
    /// </summary>
    virtual void currentValue() const = 0;

    /// <summary>
    /// Asynchronously sets the new value for this setting.
    /// </summary>
    /// <param name="newValue">
    /// The new value to set for this setting.
    /// </param>
    virtual void setValue(std::string newValue) = 0;

    // protected construction and destruction methods
protected:
    virtual ~ISetting() = default;
};
}