///
///\author Bartosz Minch <minch@agh.edu.pl>
///\date 13.05.2019
///

#include <gtest/gtest.h>
#include <threading/ThreadPool.h>

namespace libivhd_test
{
	int multiply(const int a, const int b)
	{
		const auto res = a * b;
		return res;
	}
	
	TEST(ThreadPool, DefaultThreadPool)
	{
		//// Create pool with 3 threads
		viskit::threading::ThreadPool pool(3);

		//// Submit (partial) multiplication table
		for (auto i = 1; i < 20; ++i) {
			for (auto j = 1; j < 40; ++j) {
				auto result = pool.enqueue(multiply, i, j);
				ASSERT_EQ(result.get(), i * j);
			}
		}
	}
}
