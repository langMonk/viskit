#pragma once

#include "ShaderLoader.h"
#include "TextureLoader.h"
#include "MainWindow.h"

#include <ivhd/IParticleSystem.h>
#include <QOpenGLWidget>
#include <QDebug>
#include "IRenderer.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class QOpenGLShaderProgram;

class OpenGLRenderer : public QOpenGLWidget, public virtual IRenderer
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

protected slots:
	void destroy() override;
	void update() override;  

public slots:
	void dockUndock();

private:
	struct Camera
	{
		float camDistance;
		glm::vec3 cameraDir;
		glm::mat4 modelviewMatrix;
		glm::mat4 projectionMatrix;
	} camera;

	ShaderProgram m_program;
	unsigned int m_bufPos{ 0 };
	unsigned int m_bufCol{ 0 };
	unsigned int m_vao{ 0 };
	unsigned int m_texture{ 0 };

	std::shared_ptr<ivhd::IParticleSystem> m_particleSystem;

	void printVersionInformation();

	friend class MainWindow;
};
