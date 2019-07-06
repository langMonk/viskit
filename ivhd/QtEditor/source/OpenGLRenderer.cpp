#include <QDebug>
#include <QString>
#include <QApplication>
#include <QOpenGLShaderProgram>
#include <QDesktopWidget>
#include <QExposeEvent>

#include "vertex.h"
#include "MainWindow.h"
#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(QWidget* parent)
{
	m_transform.translate(0.0f, 0.0f, -5.0f);
}

void OpenGLRenderer::generate(std::shared_ptr<ivhd::IParticleSystem> sys)
{
	
	m_particleSystem = sys;

	const size_t count = m_particleSystem->countAlive();

	{
		// Create VAO
		m_vao = new QOpenGLVertexArrayObject(this);
		m_vao->create();
		m_vao->bind();

		// Cache Uniform Locations
		u_modelToWorld = m_shaderProgram->uniformLocation("modelToWorld");
		u_worldToCamera = m_shaderProgram->uniformLocation("worldToCamera");
		u_cameraToView = m_shaderProgram->uniformLocation("cameraToView");

		// Create position VBO
		m_bufferPos = std::make_unique<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer);
		m_bufferPos->create();
		m_bufferPos->setUsagePattern(QOpenGLBuffer::StreamDraw);
		m_bufferPos->bind();

		auto positions = MainWindow::instance()->particleSystem()->finalData()->m_pos.get();
		m_bufferPos->allocate(positions, 4 * sizeof(float) * count);
		m_shaderProgram->enableAttributeArray("position");
		m_shaderProgram->setAttributeBuffer("position" , GL_FLOAT, 0, 4);

		// Create color VBO
		m_bufferColor = std::make_unique<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer);
		m_bufferColor->create();
		m_bufferColor->setUsagePattern(QOpenGLBuffer::StreamDraw);
		m_bufferColor->bind();
		auto colors = MainWindow::instance()->particleSystem()->finalData()->m_col.get();
		m_bufferColor->allocate(colors, 4 * sizeof(float) * count);
		m_shaderProgram->enableAttributeArray("color");
		m_shaderProgram->setAttributeBuffer("color", GL_FLOAT, 0, 4);

		// Release (unbind) all
		m_bufferPos->release();
		m_bufferColor->release();
		m_vao->release();
	}

	particleSystemGenerated = true;
}

void OpenGLRenderer::initializeGL()
{
	initializeOpenGLFunctions();
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLRenderer::destroy, Qt::DirectConnection);
	connect(this, &QOpenGLWidget::frameSwapped, this, &OpenGLRenderer::update);
	printVersionInformation();

	// Create Shader
	m_shaderProgram = std::make_unique<QOpenGLShaderProgram>();
	m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "./shaders/vertexShader.vert");
	m_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "./shaders/fragmentShader.frag");
	m_shaderProgram->link();
	m_shaderProgram->bind();

	if (m_particleSystem != nullptr)
	{
		generate(m_particleSystem);
		return;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	m_shaderProgram->release();
}

void OpenGLRenderer::resizeGL(int width, int height)
{
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void OpenGLRenderer::paintGL()
{
	render();
}

void OpenGLRenderer::render()
{
	if (!particleSystemGenerated) { return; }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_vao->bind();

	const size_t count = MainWindow::instance()->particleSystem()->countAlive();
	if (count > 0)
	{
		glDrawArrays(GL_POINTS, 0, count);
	}		

	m_vao->release();
	
}

void OpenGLRenderer::keyPressEvent(QKeyEvent* event)
{
	static const float transSpeed = 0.05f;

	QVector3D translation;
	if (event->key() == Qt::Key_W)
	{
		translation += m_camera.forward();
	}
	if (event->key() == Qt::Key_S)
	{
		translation -= m_camera.forward();
	}
	if (event->key() == Qt::Key_A)
	{
		translation -= m_camera.right();
	}
	if (event->key() == Qt::Key_D)
	{
		translation += m_camera.right();
	}

	m_camera.translate(transSpeed * translation);
	m_transform.rotate(1.0f, QVector3D(0.2f, 0.1f, 0.1f));

	QOpenGLWidget::update();
}

void OpenGLRenderer::destroy()
{
	m_bufferColor->destroy();
	m_bufferPos->destroy();
	m_shaderProgram->release();
}

void OpenGLRenderer::update()
{
	if (!particleSystemGenerated) { return; }

	const size_t count = m_particleSystem->countAlive();
	if (count > 0)
	{
		m_bufferPos->bind();
		auto positions = MainWindow::instance()->particleSystem()->finalData()->m_col.get();
		m_bufferColor->allocate(positions, 4 * sizeof(float) * count);

		m_bufferColor->bind();
		auto colors = MainWindow::instance()->particleSystem()->finalData()->m_col.get();
		m_bufferColor->allocate(colors, 4 * sizeof(float) * count);

		m_bufferPos->release();
		m_bufferColor->release();
	}

	// Schedule a redraw
	QOpenGLWidget::update();
}

void OpenGLRenderer::printVersionInformation()
{
	QString glType;
	QString glVersion;
	QString glProfile;

	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format().profile())
	{
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

void OpenGLRenderer::dockUndock()
{
	auto mainWindow = MainWindow::instance();
	if (parent()) 
	{
		setParent(0);
		setAttribute(Qt::WA_DeleteOnClose);
		move(QApplication::desktop()->width() / 2 - width() / 2,
			QApplication::desktop()->height() / 2 - height() / 2);
		mainWindow->setCentralWidget(nullptr);
		show();
	}
	else 
	{
		if (!mainWindow->centralWidget())
		{
			if (mainWindow->isVisible())
			{
				setAttribute(Qt::WA_DeleteOnClose, false);
				mainWindow->setCentralWidget(this);
			}
			else 
			{
				QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
			}
		}
		else 
		{
			QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
		}
	}
}