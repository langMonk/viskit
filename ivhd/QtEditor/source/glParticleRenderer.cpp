#include <particles/ParticleData.h>
#include <core/ParticleSystem.h>
#include <assert.h>

#include <GL/glew.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "glParticleRenderer.h"
#include "ShaderLoader.h"


GLParticleRenderer::GLParticleRenderer(QWidget* parent)
	: QOpenGLWidget(parent)
	, m_xRot(0)
	, m_yRot(0)
	, m_zRot(0)
	, m_program(0)
{
}

void GLParticleRenderer::yRotationChanged(int angle)
{
}

void GLParticleRenderer::zRotationChanged(int angle)
{
}

void GLParticleRenderer::initializeGL()
{
	initializeOpenGLFunctions();

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	camera.cameraDir[0] = 0.0f;
	camera.cameraDir[1] = 0.0f;
	camera.cameraDir[2] = 1.0f;
	camera.camDistance = 1.0f;

	m_program = new QOpenGLShaderProgram;
	if (!shaderLoader::loadAndBuildShaderPairFromFile(m_program, "shaders/vertexShader.vert", "shaders/fragmentShader.frag"))
	{
		assert("Shader not created properly!");
	}
		
	const size_t count = m_system->countAlive();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_bufPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * count, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4) * sizeof(float), (void*)((0) * sizeof(float)));

	glGenBuffers(1, &m_bufCol);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * count, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, (4) * sizeof(float), (void*)((0) * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLParticleRenderer::paintGL()
{
	update();
	render();

	//m_program->release();
}

void GLParticleRenderer::resizeGL(int w, int h)
{
}

void GLParticleRenderer::mousePressEvent(QMouseEvent* event)
{
}

void GLParticleRenderer::mouseMoveEvent(QMouseEvent* event)
{
}

void GLParticleRenderer::attachParticleSystem(ivhd::IParticleSystem* sys)
{
	assert(sys != nullptr);

	m_system = sys;
}

void GLParticleRenderer::destroy()
{
	if (m_bufPos != 0)
	{
		glDeleteBuffers(1, &m_bufPos);
		m_bufPos = 0;
	}

	if (m_bufCol != 0)
	{
		glDeleteBuffers(1, &m_bufCol);
		m_bufCol = 0;
	}

	makeCurrent();

	delete m_program;
}

void GLParticleRenderer::update()
{
	assert(m_system != nullptr);
	assert(m_bufPos > 0 && m_bufCol > 0);

	const size_t count = m_system->countAlive();
	if (count > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
		float* ptr = (float*)(m_system->finalData()->m_pos.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
		ptr = (float*)(m_system->finalData()->m_col.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void GLParticleRenderer::render()
{
	glBindVertexArray(m_vao);

	const size_t count = m_system->countAlive();
	if (count > 0)
		glDrawArrays(GL_POINTS, 0, count);

	glBindVertexArray(0);
}

void GLParticleRenderer::setYRotation(int angle)
{
}

void GLParticleRenderer::setZRotation(int angle)
{
}


