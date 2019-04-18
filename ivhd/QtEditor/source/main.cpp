#include "QtEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtEditor w;
	w.show();
	return a.exec();
}
