#include <QFileDialog>
#include <QDesktopServices>

#include "MainWindow.h"
#include "OpenGLRenderer.h"

void MainWindow::setCurrentCaster(std::shared_ptr<ivhd::ICaster> caster)
{
	if (caster != nullptr)
	{
		m_currentCaster = caster;
	}
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setupIVHD();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	m_renderer->onKeyPressedEvent(event);
}

void MainWindow::setupIVHD()
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
	m_casters = ivhd::createResourceCollection<ivhd::ICaster>();
	
	m_particleSystem = m_ivhd->resourceFactory().createParticleSystem();

	// initialize casters and add it to casters collection
	auto casterRandom = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::Random);
	m_casters->add("Random", casterRandom);

	//// initialize Casters Combo Box
	m_casters->iterate([&](std::string name) {
		ui.comboBox_CastingSetup->addItem(QString::fromStdString(name));
	});

	// set Random as startup currentCaster
	setCurrentCaster(casterRandom);
}

void MainWindow::on_pushButton_Open_clicked()
{
	if (!m_particleSystem->empty())
	{
		m_particleSystem->clear();
	}

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
		parser->loadFile(fileName.toUtf8().constData(), m_particleSystem);
	}

	m_casters->find("Random")->castParticleSystem(m_particleSystem);

	m_renderer = new OpenGLRenderer();
	setCentralWidget(m_renderer);
}

void MainWindow::on_pushButton_Exit_clicked()
{
	close();
}

void MainWindow::on_pushButton_CastingRun_clicked()
{
	if (m_currentCaster != nullptr)
	{
		m_currentCaster->castParticleSystem(m_particleSystem);
		m_renderer->update();
		m_renderer->repaint();
	}
	else
	{
		
	}
}
