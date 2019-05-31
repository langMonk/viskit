#include <QFileDialog>
#include <QDesktopServices>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	auto handler = [&](ivhd::LogLevel level, std::string message)
	{
		switch (level)
		{
			case ivhd::LogLevel::Info: ui.textBrowser_log->append("Info: " + QString::fromStdString(message)); break;
			case ivhd::LogLevel::Warning: ui.textBrowser_log->append("Warning: " + QString::fromStdString(message)); break;
			case ivhd::LogLevel::Error: ui.textBrowser_log->append("Error: " + QString::fromStdString(message)); break;
		}
	};

	m_ext_ivhd = ivhd::createIVHD(handler);
	ui.opengl_widget->generate(&m_ext_ivhd->particleSystem());
}

void MainWindow::on_pushButton_Open_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Choose dataset"), "",
		tr("CSV format(*.csv);;All Files (*)"));

	if (fileName.isEmpty())
	{
		return;
	}
	else
	{
		auto parser = m_ext_ivhd->resourceFactory().createParser(ivhd::ParserType::Csv);
		m_ext_ivhd->loadDataFile(fileName.toUtf8().constData(), parser);
	}

	auto casterRandom = m_ext_ivhd->resourceFactory().createCaster(ivhd::CasterType::Random);
	m_ext_ivhd->particleSystem().castData(casterRandom);
}

void MainWindow::on_pushButton_Exit_clicked()
{
	close();
}