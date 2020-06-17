#include "utils/TimeProfiler.h"

namespace viskit::utils
{
	TimeProfiler::TimeProfiler(const bool saveToFile)
	{
		m_useFile = saveToFile;
		if (m_useFile)
		{
			m_file.open("measurement.txt");
		}
	}

	void TimeProfiler::start()
	{
		m_startTime = Clock::now();
	}

	void TimeProfiler::stop()
	{
		m_stopTime = Clock::now();
	}

	size_t TimeProfiler::measurementNs()
	{
		const auto delta = duration_cast<nanoseconds>(m_stopTime - m_startTime).count();
		if (m_useFile)
		{
			m_file << delta << std::endl;
		}
		return delta;
	}

	size_t TimeProfiler::measurementMs()
	{
		const auto delta = duration_cast<milliseconds>(m_stopTime - m_startTime).count();
		if (m_useFile)
		{
			m_file << delta << std::endl;
		}
		return delta;
	}
}