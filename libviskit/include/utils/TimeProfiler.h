#pragma once

#include <fstream>
#include <iostream>
#include <chrono>

using namespace std::chrono;

using Clock = high_resolution_clock;

namespace viskit::utils
{
	// Very simple time profiling class for testing method's execution time
	class TimeProfiler
	{
		// public construction and destruction methods
	public:
		explicit TimeProfiler(bool saveToFile);
		~TimeProfiler() = default;

		// public methods
		void start();
		void stop();
		size_t measurementNs();
		size_t measurementMs();

		// private members
	private:
        high_resolution_clock::time_point m_startTime;
        high_resolution_clock::time_point m_stopTime;
		bool m_useFile{ false };
		std::ofstream m_file{};
	};
}