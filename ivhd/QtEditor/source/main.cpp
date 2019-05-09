#include "QtEditor.h"
#include <QtWidgets/QApplication>

#include <ivhd/InteractiveVizualizationBuilder.h>
#include <ivhd/IResourceFactory.h>

int main(int argc, char *argv[])
{
	std::shared_ptr<ivhd::IInteractiveVizualization> ivhd = ivhd::createIVHD();
	auto parser = ivhd->resourceFactory().createParser(ivhd::ParserType::Csv);
	ivhd->loadDataFile("D:/Datasets/mnist_7k_pca30.csv", *parser);

	QApplication a(argc, argv);
	QtEditor w;
	w.show();
	return a.exec();
}
