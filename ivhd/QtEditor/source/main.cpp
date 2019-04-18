#include "QtEditor.h"
#include <QtWidgets/QApplication>

#include <ivhd/InteractiveVizualizationBuilder.h>

int main(int argc, char *argv[])
{
	std::shared_ptr<ivhd::IInteractiveVizualization> ivhd = ivhd::createIVHD();
	QApplication a(argc, argv);
	QtEditor w;
	w.show();
	return a.exec();
}
