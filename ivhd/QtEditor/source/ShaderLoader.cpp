#include "ShaderLoader.h"

namespace shaderLoader
{
	bool loadAndBuildShaderPairFromFile(QOpenGLShaderProgram* outProg, const char* vs, const char* fs)
	{
		assert(outProg != NULL && "create the object for shader first!");
		assert(vs && fs);

		QOpenGLShaderProgram* vert = new QOpenGLShaderProgram();
		if (vert->addShaderFromSourceFile(QOpenGLShader::Vertex, vs) == false)
		{
			delete vert;
			return false;
		}

		QOpenGLShaderProgram* frag = new QOpenGLShaderProgram();
		if (frag->addShaderFromSourceFile(QOpenGLShader::Fragment, fs) == false)
		{
			delete frag;
			delete vert;
			return false;
		}

		outProg->bind();

		if (outProg->link() == false)
		{
			return false;
		}

		return true;
	}
}