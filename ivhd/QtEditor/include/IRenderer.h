#pragma once

#include <memory>

class IRenderer 
{
public:
	virtual void destroy() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

