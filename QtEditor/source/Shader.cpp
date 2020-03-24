#include <assert.h>
#include "Shader.h"

Shader::Shader(Type type)
	: m_type(type)
	, m_id(0)
{
}

void Shader::logShaderInfo()
{
	int infologLength = 0;
	glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		int charsWritten = 0;
		char* infoLog;
		infoLog = (char*)malloc(infologLength);
		glGetShaderInfoLog(m_id, infologLength, &charsWritten, infoLog);

		free(infoLog);
	}
}

error_t fopen_s(FILE **f, const char *name, const char *mode)
{
    error_t ret = 0;
    assert(f);
    *f = fopen(name, mode);

    if (!*f)
        ret = errno;
    return ret;
}

const char* readAllTextFromFile(const char* fname)
{
	FILE* fp;
	char* content = nullptr;

	int count = 0;

	if (fname == nullptr) return nullptr;

    fopen_s(&fp, fname, "rt");

	if (fp == nullptr)
    {
	    return nullptr;
    }

	fseek(fp, 0, SEEK_END);
	count = static_cast<int>(ftell(fp));
	rewind(fp);

	if (count > 0)
	{
		content = (char*)malloc(sizeof(char) * (count + 1));
		if (content)
		{
			count = (int)fread(content, sizeof(char), count, fp);
			content[count] = '\0';
		}
	}
	fclose(fp);

	return content;
}

bool Shader::loadFromFile(const char* fileName, const char* name)
{
	const char* vs = readAllTextFromFile(fileName);

	if (vs == NULL)
	{
		//LOG_ERROR("cannot load shader from file %s", logger::fileNameFromPath((char*)fileName));
		return false;
	}

	if (m_id > 0)
		glDeleteShader(m_id);

	m_id = glCreateShader(static_cast<GLenum>(m_type));
	glShaderSource(m_id, 1, &vs, NULL);

	free((void*)vs);

	// assign name:
	if (name == NULL)
	{
		//m_name = std::string(logger::fileNameFromPath((char*)fileName));
	}
	else
	{
		m_name = std::string(name);
	}

	return true;
}

void Shader::loadFromSource(const char* source, const char* name)
{
	if (m_id > 0)
		glDeleteShader(m_id);

	m_id = glCreateShader(static_cast<GLenum>(m_type));

	glShaderSource(m_id, 1, &source, NULL);

	// assign name:
	if (name == NULL)
		m_name = std::string("FROM SOURCE");
	else
		m_name = std::string(name);
}

bool Shader::compile()
{
	//assert(m_id > 0 && "id is null so the shader source should be loaded first!");

	glCompileShader(m_id);

	// check:
	int compileStatus = GL_TRUE;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE)
	{
		//LOG_ERROR("Compilation for %s shader failed!", m_name.c_str());
		logShaderInfo();
		return false;
	}

	return true;
}
