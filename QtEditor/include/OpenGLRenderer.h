#pragma once

#include "ShaderLoader.h"
#include "MainWindow.h"
#include <ivhd/IParticleSystem.h>
#include <QOpenGLWidget>
#include <QDebug>
#include "IRenderer.h"
#include "Camera.h"

class QOpenGLShaderProgram;

class OpenGLRenderer : public QOpenGLWidget, public virtual IRenderer
{
	Q_OBJECT

public:
	explicit OpenGLRenderer(QWidget* parent = 0); 
	void render() override;
	void setBoundingBox(glm::vec4 bounding_box_min, glm::vec4 bounding_box_max) override;
	
	// OpenGL Events
protected:
	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

public:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

protected slots:
	void destroy() override;
	void update() override;  

private:
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;
	
	Camera m_camera { glm::vec3(0.0f, 0.0f, 3.0f) };
	
	float lastX{};
	float lastY{};
	bool firstMouse = true;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	
	ShaderProgram m_program;
	unsigned int m_bufPos{ 0 };
	unsigned int m_bufCol{ 0 };
	unsigned int m_vao{ 0 };
	unsigned int m_texture{ 0 };

	ivhd::IParticleSystem* m_particleSystem;
	QTimer* m_timer;
	
	void printVersionInformation() const;

	friend class MainWindow;
};
