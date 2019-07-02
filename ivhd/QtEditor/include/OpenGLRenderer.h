#pragma once

#include <ivhd/IParticleSystem.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include "Transform3d.h"
#include "Camera3D.h"
#include "IRenderer.h"

class QOpenGLShaderProgram;

class OpenGLRenderer : public QOpenGLWidget ,
	protected QOpenGLFunctions, public virtual IRenderer
{
	Q_OBJECT

public:
	explicit OpenGLRenderer(QWidget* parent = 0); 
	void generate(std::shared_ptr<ivhd::IParticleSystem> sys);
	void render() override;

	// OpenGL Events
protected:
	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent* event) override;
	/*void keyReleaseEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);*/

protected slots:
	void destroy() override;
	void update() override;  

public slots:
	void dockUndock();

private:
	QOpenGLBuffer m_bufferPos, m_bufferColor;
	QOpenGLVertexArrayObject m_vao{ 0 };
	std::unique_ptr<QOpenGLShaderProgram> m_program;
	std::shared_ptr<ivhd::IParticleSystem> m_particleSystem;
	bool particleSystemGenerated{ false };

	int u_modelToWorld;
	int u_worldToCamera;
	int u_cameraToView;
	QMatrix4x4 m_projection;
	Camera3D m_camera;
	Transform3D m_transform;

	void printVersionInformation();
};
