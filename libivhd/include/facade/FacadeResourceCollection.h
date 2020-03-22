#pragma once

#include "ivhd/IResourceCollection.h"

namespace ivhd::facade
{
	template<typename T>
	class FacadeResourceCollection : public IResourceCollection<T>
	{
	public:
		FacadeResourceCollection();

	public:
		bool add(std::string name, std::shared_ptr<T> object) override;

		bool remove(std::string name) override;

		std::shared_ptr<T> find(std::string name) override;

		void clear() override;

		size_t size() override;

		void iterate(IterateCallback callback) override;

	private:
		std::map<std::string, std::shared_ptr<T>> m_data;
	};

	template<typename T>
	FacadeResourceCollection<T>::FacadeResourceCollection()
	{
	}

	template <typename T>
	bool FacadeResourceCollection<T>::add(std::string name, std::shared_ptr<T> object)
	{
		return m_data.emplace(std::move(name), object).second;
	}

	template <typename T>
	bool FacadeResourceCollection<T>::remove(std::string name)
	{
		auto found = m_data.find(name);
		if (found != m_data.end())
		{
			m_data.erase(found);
			return true;
		}

		return false;
	}

	template <typename T>
	std::shared_ptr<T> FacadeResourceCollection<T>::find(std::string name)
	{
		auto found = m_data.find(name);
		return (found != m_data.end()) ? found->second : nullptr;
	}

	template <typename T>
	void FacadeResourceCollection<T>::clear()
	{
		m_data.clear();
	}

	template <typename T>
	size_t FacadeResourceCollection<T>::size()
	{
		return m_data.size();
	}

	template <typename T>
	void FacadeResourceCollection<T>::iterate(IterateCallback callback)
	{
		for (auto it = m_data.begin(); it != m_data.end(); ++it)
		{
			callback(it->first);
		}
	}
}
