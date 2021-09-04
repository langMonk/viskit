///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#include <viskit/core/Core.h>

namespace viskit::core
{
	Core::Core(const OnLogAdded& handler)
		: m_logHandler(handler)
		, m_system(handler)
		, m_threadPool(threading::ThreadPool(1))
	{

	}

	void Core::enqueueToThreadPool(const std::function<void()>& task)
	{
		std::scoped_lock lock(m_lock);
		m_threadPool.enqueue(task);
	}
}
