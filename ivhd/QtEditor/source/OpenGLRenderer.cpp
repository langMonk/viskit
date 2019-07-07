#include "OpenGLRenderer.h"

GLfloat vertices_position[24] = {
	0.0, 0.0,
	0.5, 0.0,
	0.5, 0.5,

	0.0, 0.0,
	0.0, 0.5,
	- 0.5, 0.5,

	0.0, 0.0,
	- 0.5, 0.0,
	- 0.5, -0.5,

	0.0, 0.0,
	0.0, -0.5,
	0.5, -0.5,
};

OpenGLRenderer::OpenGLRenderer(QWidget* parent)
{

}

void OpenGLRenderer::generate(std::shared_ptr<ivhd::IParticleSystem> sys)
{
	
	
}

void OpenGLRenderer::initializeGL()
{
	glewInit();
	connect(this, &QOpenGLWidget::frameSwapped, this, &OpenGLRenderer::update);
	printVersionInformation();

	if (!shaderLoader::loadAndBuildShaderPairFromFile(&m_program, "shaders/vertexShader.vert", "shaders/fragmentShader.frag"))
	{
		std::cout << "It's not working!" << std::endl;
	}

	m_program.use();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_bufPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);
	GLint position_attribute = glGetAttribLocation(m_program.getId(), "position");
	glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_attribute);

	glEnable(GL_PROGRAM_POINT_SIZE);

}

void OpenGLRenderer::resizeGL(int width, int height)
{

}

void OpenGLRenderer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, 12);
}

void OpenGLRenderer::render()
{
	
}

void OpenGLRenderer::keyPressEvent(QKeyEvent* event)
{

}

void OpenGLRenderer::destroy()
{
	
}

void OpenGLRenderer::update()
{
	
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

void OpenGLRenderer::dockUndock()
{
	//auto mainWindow = MainWindow::instance();
	//if (parent()) 
	//{
	//	setParent(0);
	//	setAttribute(Qt::WA_DeleteOnClose);
	//	move(QApplication::desktop()->width() / 2 - width() / 2,
	//		QApplication::desktop()->height() / 2 - height() / 2);
	//	mainWindow->setCentralWidget(nullptr);
	//	show();
	//}
	//else 
	//{
	//	if (!mainWindow->centralWidget())
	//	{
	//		if (mainWindow->isVisible())
	//		{
	//			setAttribute(Qt::WA_DeleteOnClose, false);
	//			mainWindow->setCentralWidget(this);
	//		}
	//		else 
	//		{
	//			QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
	//		}
	//	}
	//	else 
	//	{
	//		QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
	//	}
	//}
}