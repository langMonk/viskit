#include <QFileDialog>
#include <QDesktopServices>

#include "MainWindow.h"
#include "OpenGLRenderer.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createIVHD();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	m_renderer->onKeyPressedEvent(event);
}

void MainWindow::createIVHD()
{
	auto handler = [&](ivhd::LogLevel level, std::string message)
	{
		switch (level)
		{
		case ivhd::LogLevel::Info: ui.textBrowser_log->append("Info: " + QString::fromStdString(message)); break;
		case ivhd::LogLevel::Warning: ui.textBrowser_log->append("Warning: " + QString::fromStdString(message)); break;
		case ivhd::LogLevel::Error: ui.textBrowser_log->append("Error: " + QString::fromStdString(message)); break;
		}
	};

	m_ivhd = ivhd::createIVHD(handler);
	m_ivhd_particleSystem = m_ivhd->resourceFactory().createParticleSystem();	
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
		auto parser = m_ivhd->resourceFactory().createParser(ivhd::ParserType::Csv);
		parser->loadFile(fileName.toUtf8().constData(), m_ivhd_particleSystem);
	}

	auto casterRandom = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::Random);
	casterRandom->castParticleSystem(m_ivhd_particleSystem);

	m_renderer = new OpenGLRenderer();
	setCentralWidget(m_renderer);
}

void MainWindow::on_pushButton_Exit_clicked()
{
	close();
}

void MainWindow::on_pushButton_CastingRun()
{
}
