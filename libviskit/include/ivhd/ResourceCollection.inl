#include <string>

#include "ResourceCollection.h"

namespace ivhd {
    template<typename T>
    bool ResourceCollection<T>::add(std::string name, std::shared_ptr <T> object) {
        return m_data.emplace(std::move(name), object).second;
    }

    template<typename T>
    bool ResourceCollection<T>::remove(std::string name) {
        auto found = m_data.find(name);
        if (found != m_data.end()) {
            m_data.erase(found);
            return true;
        }

        return false;
    }

    template<typename T>
    std::shared_ptr <T> ResourceCollection<T>::find(std::string name) {
        auto found = m_data.find(name);
        return (found != m_data.end()) ? found->second : nullptr;
    }

    template<typename T>
    void ResourceCollection<T>::clear() {
        m_data.clear();
    }

    template<typename T>
    size_t ResourceCollection<T>::size() {
        return m_data.size();
    }

    template<typename T>
    void ResourceCollection<T>::iterate(IterateCallback callback) {
        for (auto it = m_data.begin(); it != m_data.end(); ++it) {
            callback(it->first);
        }
    }

    template<typename T>
    ResourceCollection<T>::~ResourceCollection() {

    }

    template<typename T>
    ResourceCollection<T>::ResourceCollection() : m_data(){

    }
}