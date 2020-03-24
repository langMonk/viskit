#pragma once

#include <vector>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram(ShaderProgram&&) = default;

	ShaderProgram& operator=(const ShaderProgram&) = delete;
	ShaderProgram& operator=(ShaderProgram&&) = default;

	void create();
	void attachShader(Shader* shader);
	bool link();
	bool validate();

	inline void  use();
	inline void  disable();
	inline GLint getUniformLocation(const char* varName);

	inline bool uniform1i(const char* varName, int value);
	inline bool uniform1f(const char* varName, float value);
	inline bool uniform2f(const char* varName, float x, float y);
	inline bool uniform3f(const char* varName, float x, float y, float z);
	inline bool uniform4f(const char* varName, float x, float y, float z, float w);
	inline bool uniform1fv(const char* varName, GLuint count, float* values);
	inline bool uniform3fv(const char* varName, float* values);
	inline bool uniform4fv(const char* varName, float* values);
	inline bool uniformMatrix3f(const char* varName, float* mat, bool transpose = false);
	inline bool uniformMatrix4f(const char* varName, float* mat, bool transpose = false);

	GLuint getId() const { return m_id; }
	
private:
	void destroy();
	void logProgramInfo();

private:
	GLuint m_id;
	std::vector<Shader*> m_shaders;
};

inline void ShaderProgram::use()
{
	glUseProgram(m_id);
}

inline void ShaderProgram::disable()
{
	glUseProgram(0);
}

inline GLint ShaderProgram::getUniformLocation(const char* varName)
{
	//assert(mId > 0 && "create the program id first!");
	GLint i = glGetUniformLocation(m_id, varName);

	return i;
}

inline bool ShaderProgram::uniform1i(const char* varName, int value)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform1i(i, value);
	return true;
}

inline bool ShaderProgram::uniform1f(const char* varName, float value)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform1f(i, value);
	return true;
}

inline bool ShaderProgram::uniform2f(const char* varName, float x, float y)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform2f(i, x, y);
	return true;
}

inline bool ShaderProgram::uniform3f(const char* varName, float x, float y, float z)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform3f(i, x, y, z);
	return true;
}

inline bool ShaderProgram::uniform4f(const char* varName, float x, float y, float z, float w)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform4f(i, x, y, z, w);
	return true;
}

inline bool ShaderProgram::uniform1fv(const char* varName, GLuint count, float* values)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform1fv(i, count, values);
	return true;
}

inline bool ShaderProgram::uniform3fv(const char* varName, float* values)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform3fv(i, 1, values);
	return true;
}

inline bool ShaderProgram::uniform4fv(const char* varName, float* values)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniform4fv(i, 1, values);
	return true;
}

inline bool ShaderProgram::uniformMatrix3f(const char* varName, float* mat, bool transpose)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniformMatrix3fv(i, 1, transpose, mat);
	return true;
}

inline bool ShaderProgram::uniformMatrix4f(const char* varName, float* mat, bool transpose)
{
	GLint i = getUniformLocation(varName);
	if (i == -1) return false;

	glUniformMatrix4fv(i, 1, transpose, mat);
	return true;
}
