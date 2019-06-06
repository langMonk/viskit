#pragma once

#include <memory>

class IRenderer 
{
public:
	virtual void destroy() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

class RendererFactory
{
public:
	static std::shared_ptr<IRenderer> create(const char* name);
};
