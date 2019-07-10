#include "MainWindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// Load an application style
	QFile styleFile("./style/MaterialDark.qss");
	styleFile.open(QFile::ReadOnly);

	// Apply the loaded stylesheet
	QString style(styleFile.readAll());
	app.setStyleSheet(style);

	auto w = MainWindow::instance();
	w->show();

	return app.exec();
}
