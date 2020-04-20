#pragma once

#include <cuda_runtime.h>

enum DistElemType { etNear, etFar, etRandom, etToRemove };

class DistElem
{
public:
	long i, j;
	float r;
	float2* comp1;
	float2* comp2;
	DistElemType type;

	DistElem(long pi, long pj) : i(pi), j(pj), r(0), comp1(nullptr), comp2(nullptr), type(etNear) {};
	DistElem(long pi, long pj, DistElemType ptype, float pr)
		: i(pi), j(pj), r(pr), comp1(nullptr), comp2(nullptr), type(ptype) {};
};