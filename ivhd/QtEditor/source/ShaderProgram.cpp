/** @file ShaderProrgam.cpp
*  @brief useful class for shader program management and loading
*
*	@author Bartlomiej Filipek

*/

#include <algorithm>
#include "Shader.h"
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() :
	m_id(0)
{

}

ShaderProgram::~ShaderProgram()
{
	destroy();
}

void ShaderProgram::create()
{
	if (m_id > 0)
		destroy();

	m_id = glCreateProgram();
}

void ShaderProgram::attachShader(Shader* shader)
{
	//assert(shader != NULL);
	//assert(m_id > 0 && "create the program id first!");

	m_shaders.push_back(shader);
	glAttachShader(m_id, shader->getId());
}

bool ShaderProgram::link()
{
	//assert(m_id > 0 && "create the program id first!");

	glLinkProgram(m_id);

	int success = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (success == GL_FALSE)
	{
		logProgramInfo();
		return false;
	}

	return true;
}

bool ShaderProgram::validate()
{
	glValidateProgram(m_id);
	GLint status;
	glGetProgramiv(m_id, GL_VALIDATE_STATUS, &status);

	if (!status)
		logProgramInfo();

	return status == GL_TRUE;
}

void ShaderProgram::destroy()
{
#if _MSC_VER >= 1600
	// lambda :)
	std::for_each(m_shaders.begin(), m_shaders.end(), [&](Shader* sh) {
		glDetachShader(m_id, sh->getId());
		delete sh;
	});
#else
	for (unsigned int i = 0; i < m_shaders.size(); ++i)
	{
		glDetachShader(m_id, m_shaders[i]->getId());
		delete m_shaders[i];
	}
#endif

	m_shaders.clear();

	if (m_id > 0)
		glDeleteProgram(m_id);

	m_id = 0;
}

void ShaderProgram::logProgramInfo()
{
	int infologLength = 0;
	int charsWritten = 0;

	glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0)
	{
		char* infoLog = (char*)malloc(infologLength);
		glGetProgramInfoLog(m_id, infologLength, &charsWritten, infoLog);

		free(infoLog);
	}
}
