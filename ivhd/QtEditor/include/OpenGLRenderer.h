#pragma once

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
	void render() override;

	// OpenGL Events
protected:
	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent* event) override;
	//void keyReleaseEvent(QKeyEvent* event) override;
	//void mousePressEvent(QMouseEvent* event) override;
	//void mouseReleaseEvent(QMouseEvent* event) override;

protected slots:
	void destroy() override;
	void update() override;  

public slots:
	void dockUndock();

private:
	// OpenGL State Information
	QOpenGLBuffer m_vertex;
	QOpenGLVertexArrayObject m_object{ 0 };
	QOpenGLShaderProgram* m_program{ 0 };

	// Shader Information
	int u_modelToWorld;
	int u_worldToCamera;
	int u_cameraToView;
	QMatrix4x4 m_projection;
	Camera3D m_camera;
	Transform3D m_transform;

	// Private Helpers
	void printVersionInformation();
};
