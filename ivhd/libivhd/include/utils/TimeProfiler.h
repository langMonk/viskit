#pragma once

#include <fstream>
#include <iostream>
#include <chrono>

using namespace std::chrono;

using Clock = high_resolution_clock;

namespace ivhd::utils
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
		time_point<steady_clock> m_startTime;
		time_point<steady_clock> m_stopTime;
		bool m_useFile{ false };
		std::ofstream m_file{};
	};
}