#include "MainWindow.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	//QSurfaceFormat format;
	//format.setRenderableType(QSurfaceFormat::OpenGL);
	//format.setProfile(QSurfaceFormat::CoreProfile);
	//format.setVersion(4, 6);

	// Set widget up
	//OpenGLRenderer* w = new OpenGLRenderer;
	//w->resize(QSize(1280, 720));
	//// Set the window up
	//QMainWindow window;
	//window.setCentralWidget(widget);
	//window.resize(QSize(800, 600));
	//window.show();

	auto w = MainWindow::instance();
	w->show();

	return app.exec();
}
