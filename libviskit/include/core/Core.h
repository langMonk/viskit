///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include "Logger.h"
#include "System.h"
#include "threading/ThreadPool.h"

namespace viskit::core
{
	class Core
	{
		// public construction and destruction methods
	public:
		explicit Core(const OnLogAdded& handler);

		// public methods
	public:
		Logger& logger() { return m_system.logger(); }

		System& system() { return m_system; }

		void enqueueToThreadPool(const std::function<void()>& task);

	private:
		OnLogAdded m_logHandler;
		System m_system;
		
		threading::ThreadPool m_threadPool;
		std::mutex m_lock;
	};
}