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
	const size_t count = MainWindow::instance()->particleSystem()->countAlive();
	m_particleSystem = sys;
	{
		// Create Shader
		m_program = std::make_unique<QOpenGLShaderProgram>();
		m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "./shaders/vertexShader.vert");
		m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "./shaders/fragmentShader.frag");
		m_program->link();
		m_program->bind();

		// Cache Uniform Locations
		u_modelToWorld = m_program->uniformLocation("modelToWorld");
		u_worldToCamera = m_program->uniformLocation("worldToCamera");
		u_cameraToView = m_program->uniformLocation("cameraToView");

		// Create position VBO
		m_bufferPos.create();
		m_bufferPos.bind();
		m_bufferPos.setUsagePattern(QOpenGLBuffer::DynamicCopy);
		m_bufferPos.allocate(m_particleSystem->finalData()->m_pos.get(), 4 * sizeof(float) * count);

		// Create color VBO
		m_bufferColor.create();
		m_bufferColor.bind();
		m_bufferColor.setUsagePattern(QOpenGLBuffer::DynamicCopy);
		m_bufferColor.allocate(m_particleSystem->finalData()->m_col.get(), 4 * sizeof(float) * count);

		// Create VAO
		m_vao.create();
		m_vao.bind();
		m_program->enableAttributeArray(0);
		m_program->enableAttributeArray(1);
		//m_program->setAttributeBuffer(0, GL_FLOAT, 0, 4*sizeof(float), 0);
		//m_program->setAttributeBuffer(1, GL_FLOAT, 0, 4*sizeof(float), 0);

		// Release (unbind) all
		m_vao.release();
		m_bufferPos.release();
		m_bufferColor.release();
		m_program->release();
	}

	particleSystemGenerated = true;
}

void OpenGLRenderer::initializeGL()
{
	if (m_particleSystem != nullptr)
	{
		generate(m_particleSystem);
		return;
	}

	initializeOpenGLFunctions();
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLRenderer::destroy, Qt::DirectConnection);
	connect(this, &QOpenGLWidget::frameSwapped, this, &OpenGLRenderer::update);
	printVersionInformation();
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
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);

	m_program->bind();
	m_program->setUniformValue(u_worldToCamera, m_camera.toMatrix());
	m_program->setUniformValue(u_cameraToView, m_projection);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	{
		m_vao.bind();

		const size_t count = MainWindow::instance()->particleSystem()->countAlive();
		if (count > 0)
		{
			glDrawArrays(GL_POINTS, 0, count);
		}		

		m_vao.release();
	}

	glDisable(GL_BLEND);
	m_program->release();
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
	m_vao.destroy();
	m_bufferColor.destroy();
	m_bufferPos.destroy();
	m_program->release();
}

void OpenGLRenderer::update()
{
	// Update instance information
	m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

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