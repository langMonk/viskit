#pragma once

#include "ShaderProgram.h"

namespace shaderLoader
{
	bool loadAndBuildShaderPairFromFile(ShaderProgram* outProg, const char* vs, const char* fs);
	bool loadAndBuildShaderPairFromSource(ShaderProgram* outProg, const char* vsSource, const char* fsSource);
} 
