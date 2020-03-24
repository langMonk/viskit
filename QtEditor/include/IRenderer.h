#pragma once

#include <memory>

class IRenderer 
{
public:
	virtual void destroy() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void setBoundingBox(glm::vec4 bounding_box_min, glm::vec4 bounding_box_max) = 0;
};

