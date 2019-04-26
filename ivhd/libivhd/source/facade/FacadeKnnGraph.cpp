#include "facade\FacadeKnnGraph.h"

namespace ivhd::facade
{
	FacadeKnnGraph::FacadeKnnGraph(core::ParticleSystem& system)
		: m_system(system)
	{
	}

	void FacadeKnnGraph::resetParams()
	{
	}

	bool FacadeKnnGraph::create()
	{
		return false;
	}

	int FacadeKnnGraph::createFromCache()
	{
		return 0;
	}

	void FacadeKnnGraph::clear()
	{

	}

	void FacadeKnnGraph::sort()
	{

	}

	bool FacadeKnnGraph::saveToCache()
	{
		return false;
	}

	bool FacadeKnnGraph::reversedNeighborsEnabled()
	{
		return false;
	}

	size_t FacadeKnnGraph::size()
	{
		return size_t();
	}

	void FacadeKnnGraph::add(DistElem& element)
	{
	}

	DistElem& FacadeKnnGraph::getElement(long index)
	{
		// TODO: insert return statement here
	}
}

