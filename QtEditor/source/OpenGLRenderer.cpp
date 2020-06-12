#include <glm/glm/gtc/type_ptr.hpp>
#include "TextureLoader.h"
#include "QKeyEvent"
#include "QTimer"
#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(QWidget* parent)
{
	m_particleSystem = &MainWindow::instance()->particleSystem();
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
	m_timer->start(100);

}

void OpenGLRenderer::initializeGL()
{
	glewInit();
	printVersionInformation();
	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.15f, 0.15f, 0.15f, 0.0f);

	if (!shaderLoader::loadAndBuildShaderPairFromFile(&m_program, "shaders/vertexShader.vert", "shaders/fragmentShader.frag"))
	{
		qDebug() << "Shader not working!";
	}

	if (!textureLoader::loadTexture(&m_texture, "images/particle.png"))
	{
		qDebug() << "Texture not loaded properly!";
	}

	glEnable(GL_POINT_SPRITE);

	m_program.use();
	m_program.uniform1i("tex", 0);
	m_program.disable();

	const auto count = m_particleSystem->countAlive();
	auto positions = m_particleSystem->positions();
	auto colors = m_particleSystem->colors();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Position VBO
	glGenBuffers(1, &m_bufPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);

	glBufferData(GL_ARRAY_BUFFER, 4 * count * sizeof(float), positions, GL_STREAM_DRAW);
	const auto position_attribute = glGetAttribLocation(m_program.getId(), "vPosition");
	glVertexAttribPointer(position_attribute, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(position_attribute);

	// Color VBO
	glGenBuffers(1, &m_bufCol);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);

	glBufferData(GL_ARRAY_BUFFER, 4 * count * sizeof(float), colors, GL_STREAM_DRAW);
	const auto color_attribute = glGetAttribLocation(m_program.getId(), "vColor");
	glVertexAttribPointer(color_attribute, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLRenderer::resizeGL(int width, int height)
{
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
}

void OpenGLRenderer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(m_camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 3500.0f);

	// camera/view transformation
	glm::mat4 modelViewMatrix = m_camera.GetViewMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glEnable(GL_PROGRAM_POINT_SIZE);

	m_program.use();
	m_program.uniformMatrix4f("matProjection", glm::value_ptr(projectionMatrix));
	m_program.uniformMatrix4f("matModelView", glm::value_ptr(modelViewMatrix));
	m_program.uniform2f("screenSize", static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT));
	m_program.uniform1f("spriteSize", 20.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	update();
	render();

	glDisable(GL_BLEND);

	m_program.disable();
}

void OpenGLRenderer::render()
{
	glBindVertexArray(m_vao);

	const auto count = m_particleSystem->countAlive();
	if (count > 0)
	{
		glDrawArrays(GL_POINTS, 0, count);
	}

	glBindVertexArray(0);
}

void OpenGLRenderer::setBoundingBox(glm::vec4 bounding_box_min, glm::vec4 bounding_box_max)
{
	m_camera.Position.x = (bounding_box_min.x + bounding_box_max.x) / 2;
	m_camera.Position.y = (bounding_box_min.y + bounding_box_max.y) / 2;
}


void OpenGLRenderer::mousePressEvent(QMouseEvent* event)
{

}

void OpenGLRenderer::mouseMoveEvent(QMouseEvent* event)
{
	auto xpos = event->x();
	auto ypos = event->y();
	
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void OpenGLRenderer::wheelEvent(QWheelEvent* event)
{
	// m_camera.ProcessMouseScroll(event->delta());
}

void OpenGLRenderer::keyPressEvent(QKeyEvent* event)
{
	firstMouse = true;

	if (event->key() == Qt::Key_W)
	{
		m_camera.ProcessKeyboard(FORWARD, 0.25f);
	}
	else if (event->key() == Qt::Key_S)
	{
		m_camera.ProcessKeyboard(BACKWARD, 0.25f);
	}
	else if (event->key() == Qt::Key_A)
	{
		m_camera.ProcessKeyboard(LEFT, 0.25f);
	}
	else if (event->key() == Qt::Key_D)
	{
		m_camera.ProcessKeyboard(RIGHT, 0.25f);
	}

	QWidget::update();
}

void OpenGLRenderer::destroy()
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

	if (m_texture != 0)
	{
		glDeleteTextures(0, &m_texture);
		m_texture = 0;
	}
}

void OpenGLRenderer::update()
{
	const auto count = m_particleSystem->countAlive();
	if (count > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
		auto pos = m_particleSystem->positions();
		auto* ptr = reinterpret_cast<float*>(pos);
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
		auto colors = m_particleSystem->colors();
		ptr = reinterpret_cast<float*>(colors);
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void OpenGLRenderer::printVersionInformation() const
{
	QString glProfile;
	const QString glType = reinterpret_cast<const char*>(glGetString(GL_TYPE));
	const QString glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

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

//void OpenGLRenderer::dockUndock()
//{
//	//auto mainWindow = MainWindow::instance();
//	//if (parent()) 
//	//{
//	//	setParent(0);
//	//	setAttribute(Qt::WA_DeleteOnClose);
//	//	move(QApplication::desktop()->width() / 2 - width() / 2,
//	//		QApplication::desktop()->height() / 2 - height() / 2);
//	//	mainWindow->setCentralWidget(nullptr);
//	//	show();
//	//}
//	//else 
//	//{
//	//	if (!mainWindow->centralWidget())
//	//	{
//	//		if (mainWindow->isVisible())
//	//		{
//	//			setAttribute(Qt::WA_DeleteOnClose, false);
//	//			mainWindow->setCentralWidget(this);
//	//		}
//	//		else 
//	//		{
//	//			QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
//	//		}
//	//	}
//	//	else 
//	//	{
//	//		QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
//	//	}
//	//}
//}
