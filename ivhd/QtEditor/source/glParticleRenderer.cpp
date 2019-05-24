#include <particles/ParticleData.h>
#include <core/ParticleSystem.h>
#include <assert.h>

#include <GL/glew.h>

#include "glParticleRenderer.h"

bool GLParticleRenderer::m_transparent = false;

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
	glClearColor(0, 0, 0, m_transparent ? 0 : 1);

	m_program = new QOpenGLShaderProgram;
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "./vertexShader.glsl");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "./fragmentShader.glsl");
	m_program->bindAttributeLocation("vertex", 0);
	m_program->bindAttributeLocation("normal", 1);
	m_program->link();

	m_program->bind();
	m_projMatrixLoc = m_program->uniformLocation("projMatrix");
	m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
	m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
	m_lightPosLoc = m_program->uniformLocation("lightPos");

	const size_t count = 2000;

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	m_program->bind();
	m_program->setUniformValue(m_projMatrixLoc, m_proj);
	m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
	QMatrix3x3 normalMatrix = m_world.normalMatrix();
	m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

	update();
	render();

	m_program->release();
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

void GLParticleRenderer::generate(ivhd::IParticleSystem* sys)
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
}

void GLParticleRenderer::update()
{
	assert(m_system != nullptr);
	assert(m_bufPos > 0 && m_bufCol > 0);

	const size_t count = 2000;
	if (count > 0)
	{
		/*glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
		float* ptr = (float*)(m_system->finalData()->m_pos.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
		ptr = (float*)(m_system->finalData()->m_col.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);*/
	}
}

void GLParticleRenderer::render()
{
	glBindVertexArray(m_vao);

	const size_t count = 2000;
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


