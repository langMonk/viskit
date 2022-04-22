///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 19.12.2019
///

#pragma once

#include <memory>
#include <functional>
#include <map>

namespace viskit
{
    // public sub-types
    using IterateCallback = std::function<void(std::string name)>;

    template<typename T>
    class ResourceCollection
    {
        // public methods
    public:
        ResourceCollection();
        ~ResourceCollection();

        bool add(std::string name, std::shared_ptr<T> object);

        bool remove(std::string name);

        std::shared_ptr<T> find(std::string name);

        void clear();

        size_t size();

        void iterate(IterateCallback callback);

    private:
        std::map<std::string, std::shared_ptr<T>> m_data;
    };
}

#include <viskit/viskit/ResourceCollection.inl>
