#pragma once

#include <memory>
#include "OpenGLRenderer.h"

class RendererFactory
{
public:
	static std::shared_ptr<IRenderer> create(const char* name, QWidget* parent)
	{
		if (std::string(name) == "OpenGL")
		{
			return std::make_shared<OpenGLRenderer>(parent);
		}
		else
		{
			return nullptr;
		}
	}
};
