#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include "transform3d.h"
#include "IRenderer.h"

class QOpenGLShaderProgram;

class OpenGLRenderer : public QOpenGLWidget ,
	protected QOpenGLFunctions, public virtual IRenderer
{
	Q_OBJECT

		// OpenGL Events
public:
	explicit OpenGLRenderer(QWidget* parent = 0);
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void render() override;

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
	int u_modelToWorld{ 0 };
	int u_worldToView{ 0 };
	QMatrix4x4 m_projection;
	Transform3D m_transform;

	// Private Helpers
	void printVersionInformation();
};
