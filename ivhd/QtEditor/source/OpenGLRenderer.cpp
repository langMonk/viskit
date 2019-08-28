#include "QKeyEvent"
#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(QWidget* parent)
{
	m_particleSystem = MainWindow::instance()->particleSystem();
}

void OpenGLRenderer::generate(std::shared_ptr<ivhd::IParticleSystem> sys)
{
	
}

void OpenGLRenderer::initializeGL()
{
	glewInit();
	printVersionInformation();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.15f, 0.15f, 0.15f, 0.0f);

	camera.cameraDir[0] = 0.0f;
	camera.cameraDir[1] = 0.0f;
	camera.cameraDir[2] = 1.0f;
	camera.camDistance = 1.0f;
	
	if (!shaderLoader::loadAndBuildShaderPairFromFile(&m_program, "shaders/vertexShader.vert", "shaders/fragmentShader.frag"))
	{
		qDebug() << "Shader not working!";
	}

	if (!textureLoader::loadTexture(&m_texture, "data\\particle.png"))
	{
		qDebug() << "Texture not loaded properly!";
	}

	glEnable(GL_POINT_SPRITE);
	
	m_program.use();
	m_program.uniform1i("tex", 0);
	m_program.disable();

	size_t count = m_particleSystem->countAlive();
	auto data = m_particleSystem->availableData();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Position VBO
	glGenBuffers(1, &m_bufPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
	glBufferData(GL_ARRAY_BUFFER, 4 * count * sizeof(float), data->m_pos.get(), GL_STREAM_DRAW);
	GLint position_attribute = glGetAttribLocation(m_program.getId(), "vPosition");
	glVertexAttribPointer(position_attribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	// Color VBO
	glGenBuffers(1, &m_bufCol);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);

	glBufferData(GL_ARRAY_BUFFER, 4 * count * sizeof(float), data->m_col.get(), GL_STREAM_DRAW);
	GLint color_attribute = glGetAttribLocation(m_program.getId(), "vColor");
	glVertexAttribPointer(color_attribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_attribute);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLRenderer::resizeGL(int width, int height)
{
	float aspect = static_cast<float>(width / height);

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	// setup projection matrix
	camera.projectionMatrix = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
}

void OpenGLRenderer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	camera.modelviewMatrix = glm::lookAt(camera.cameraDir * camera.camDistance, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glEnable(GL_PROGRAM_POINT_SIZE);

	m_program.use();
	m_program.uniformMatrix4f("matProjection", glm::value_ptr(camera.projectionMatrix));
	m_program.uniformMatrix4f("matModelview", glm::value_ptr(camera.modelviewMatrix));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	render();
	
	glDisable(GL_BLEND);

	m_program.disable();
}

void OpenGLRenderer::render()
{
	glBindVertexArray(m_vao);

	auto count = m_particleSystem->countAlive();
	if (count > 0)
	{
		glDrawArrays(GL_POINTS, 0, count);
	}

	glBindVertexArray(0);
}

void OpenGLRenderer::onKeyPressedEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_W)
	{
		camera.camDistance -= 0.1f;
	}
	else if (event->key() == Qt::Key_S)
	{
		camera.camDistance += 0.1f;
	}
	else if (event->key() == Qt::Key_A)
	{
		camera.cameraDir.x -= 0.1f;
	}
	else if (event->key() == Qt::Key_D)
	{
		camera.cameraDir.x += 0.1f;
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
	size_t count = m_particleSystem->countAlive();
	if (count > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
		float* ptr = (float*)(m_particleSystem->availableData()->m_pos.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
		ptr = (float*)(m_particleSystem->availableData()->m_col.get());
		glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
}

void OpenGLRenderer::printVersionInformation()
{
	QString glType;
	QString glVersion;
	QString glProfile;


	glType = reinterpret_cast<const char*>(glGetString(GL_TYPE));
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