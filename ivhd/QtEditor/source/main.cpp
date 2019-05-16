#include "MainWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	auto w = MainWindow::instance();
	w->show();
	return a.exec();
}
