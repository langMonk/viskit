#pragma once

#include <GL/glew.h>

namespace textureLoader
{
	bool loadTexture(GLuint* outId, const char* filename);
}