#include "threading/ThreadFarm.h"

namespace ivhd::threading
{
	ThreadFarm::ThreadFarm(int threadNumber)
		: m_threadNumber(threadNumber)
	{
	}

	void ThreadFarm::add(std::thread thread)
	{
		m_threads.push_back(thread);
	}

	void ThreadFarm::start()
	{
		for (int i = 0; i < th_cnt; i++)
			th[i]->start();
	}

	void ThreadFarm::join()
	{
	}
}