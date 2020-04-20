#pragma once

#include <cuda_runtime.h>
#include <iostream>

constexpr auto w_random = 0.01f;
constexpr auto b_factor = 0.002f;
constexpr auto a_factor = 0.9f;

inline bool cudaCheck(cudaError_t ret, const char* fileName,
	unsigned int lineNo) {
	if (ret != cudaSuccess) {
		std::cerr << "CUDA error in " << fileName << ":" << lineNo << std::endl
			<< "\t (" << cudaGetErrorString(ret) << ")" << std::endl;
		exit(-1);
	}

	return ret != cudaSuccess;
}

#define cuCall(err) cudaCheck(err, __FILE__, __LINE__)