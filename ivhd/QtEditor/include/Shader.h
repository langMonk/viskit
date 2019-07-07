#pragma once

#include <iostream>
#include <GL/glew.h>

class Shader
{
public:
	enum class Type
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER
	};

public:
	explicit Shader(Type type);
	~Shader() = default;

	Shader(const Shader&) = delete;
	Shader(Shader&&) = default;

	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&&) = default;

	bool loadFromFile(const char* fileName, const char* name = NULL);

	void loadFromSource(const char* source, const char* name = NULL);

	bool compile();

	GLuint getId() const { return m_id; }
	const char* getName() const { return m_name.c_str(); }

private:
	GLuint m_id;
	Type   m_type;
	std::string m_name;

private:
	void logShaderInfo();

};
