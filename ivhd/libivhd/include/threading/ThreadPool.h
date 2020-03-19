#pragma once

#include <functional>
#include <future>
#include <queue>

namespace ivhd::threading
{
	class ThreadPool
	{
	public:
		explicit ThreadPool(size_t);
		template<class F, class... Args>
		decltype(auto) enqueue(F&& f, Args&&... args);
		~ThreadPool();

	private:
		std::vector<std::thread> workers;
		std::queue<std::packaged_task<void()>> tasks;

		std::mutex queue_mutex;
		std::condition_variable condition;
		bool stop;
	};

	template<class F, class... Args>
	decltype(auto) ThreadPool::enqueue(F&& f, Args&&... args)
	{
		using return_type = std::invoke_result_t<F, Args...>;

		auto task = std::make_shared<std::packaged_task<return_type()>>
			(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);

		std::future<return_type> res = task->get_future();
		{
			std::unique_lock<std::mutex> lock(queue_mutex);

			if (stop) 
				throw std::runtime_error("enqueue on stopped ThreadPool");

			tasks.emplace([task]() { (*task)(); });
		}
		condition.notify_one();
		return res;
	}
}