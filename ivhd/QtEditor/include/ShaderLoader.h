#pragma once

#include <QOpenGLShaderProgram>

namespace shaderLoader
{
	bool loadAndBuildShaderPairFromFile(QOpenGLShaderProgram* outProg, const char* vs, const char* fs);
} 
