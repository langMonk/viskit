///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <ivhd/IParticleSystem.h>
#include "IRenderer.h"

class GLParticleRenderer : public IParticleRenderer
{	
public:
	GLParticleRenderer(QWidget* parent = 0);
	~GLParticleRenderer() { destroy(); }

	void generate(ivhd::IParticleSystem* sys) override;
	void destroy() override;
	void update() override;
	void render() override;

public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	GLuint m_bufPos{ 0 };
	GLuint m_bufCol{ 0 };
	GLuint m_vao{ 0 };
	ivhd::IParticleSystem* m_system{ nullptr };
	QOpenGLShaderProgram* m_program;

	int m_projMatrixLoc;
	int m_mvMatrixLoc;
	int m_normalMatrixLoc;
	int m_lightPosLoc;

	int m_xRot;
	int m_yRot;
	int m_zRot;
	QPoint m_lastPos;

	QMatrix4x4 m_proj;
	QMatrix4x4 m_camera;
	QMatrix4x4 m_world;

	static bool m_transparent;
};