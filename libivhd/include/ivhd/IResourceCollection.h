///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.12.2019
///

#pragma once

#include <memory>
#include <functional>
#include <map>

namespace ivhd
{
	// public sub-types
	using IterateCallback = std::function<void(std::string name)>;

	template<typename T>
	class IResourceCollection
	{
		// public methods 
	public:
		/// <summary>
		/// Add new element to the list.
		/// </summary>
		/// <returns> True if action succeded.</returns>
		virtual bool add(std::string name, std::shared_ptr<T> object) = 0;

		/// <summary>
		/// Remove element from the list.
		/// </summary> 
		/// <returns> True if action succeded.</returns>
		virtual bool remove(std::string name) = 0;

		/// <summary>
		/// Find element in the list.
		/// </summary>
		/// <returns> Element if it was found.</returns>
		virtual std::shared_ptr<T> find(std::string name) = 0;

		/// <summary>
		/// Clears the list.
		/// </summary>
		virtual void clear() = 0;

		/// <summary>
		/// Collection size
		/// </summary>
		/// <returns> Returns number of elements currently in collection.</returns>
		virtual size_t size() = 0;

		/// <summary>
		/// Iterate through elements in the collection.
		/// </summary>
		virtual void iterate(IterateCallback callback) = 0;
	};
}
