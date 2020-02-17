#include <QFileDialog>

#include "MainWindow.h"
#include "OpenGLRenderer.h"

MainWindow::MainWindow(QWidget* parent)
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

	// create IVHD
	m_ivhd = ivhd::createIVHD(handler);
	initializeIVHDResources();
	initializeEditorElements();
}

void MainWindow::initializeIVHDResources()
{
	// create collections
	m_casters = ivhd::createResourceCollection<ivhd::ICaster>();
	m_generators = ivhd::createResourceCollection<ivhd::IGraphGenerator>();

	// add resources to collections
	const auto casterRandom = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::Random);
	const auto casterMDS = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::MDS);
	m_casters->add("Random", casterRandom);
	m_casters->add("MDS", casterMDS);

	const auto bruteGenerator = m_ivhd->resourceFactory().createGraphGenerator(ivhd::GraphGeneratorType::BruteForce);
	m_generators->add("Brute Force", bruteGenerator);

	// set default resources
	setCurrentCaster(casterRandom);
	setCurrentGraphGenerator(bruteGenerator);
}

void MainWindow::initializeEditorElements()
{
	// casters
	m_casters->iterate([&](std::string name) {
		ui.comboBox_CastingSetup->addItem(QString::fromStdString(name));
	});

	// graph generators
	m_generators->iterate([&](std::string name) {
		ui.comboBox_GraphSetup->addItem(QString::fromStdString(name));
	});

}

void MainWindow::on_pushButton_Open_clicked()
{
	ivhd::IParticleSystem& particleSystem = m_ivhd->particleSystem();

	if (!particleSystem.empty())
	{
		particleSystem.clear();
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
		parser->loadFile(fileName.toUtf8().constData());
	}

	m_casters->find("Random")->castParticleSystem();

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
		m_ivhd->currentCaster(m_currentCaster);
		m_ivhd->subscribeOnCastingStepFinish([&]()
		{

		});

		m_ivhd->startCasting();
		m_running = true;
	}
	else
	{

	}
}

void MainWindow::on_pushButton_CastingStop_clicked()
{
	if(m_running)
	{
		m_ivhd->stopCasting();
	}

	m_running = false;
}

void MainWindow::on_pushButton_GraphRun_clicked() const
{
	if (m_currentGraphGenerator != nullptr)
	{
		if (true)
		{
			m_currentGraphGenerator->generate(3, 0, 1);
		}
	}
	else
	{

	}
}

void MainWindow::on_comboBox_CastingSetup_activated()
{

	setCurrentCaster(m_casters->find(ui.comboBox_CastingSetup->currentText().toStdString()));
}

void MainWindow::on_comboBox_GraphSetup_activated()
{
	setCurrentGraphGenerator(m_generators->find(ui.comboBox_GraphSetup->currentText().toStdString()));
}

void MainWindow::setCurrentCaster(std::shared_ptr<ivhd::ICaster> caster)
{
	if (caster != nullptr)
	{
		m_currentCaster = caster;
	}
}

void MainWindow::setCurrentGraphGenerator(std::shared_ptr<ivhd::IGraphGenerator> generator)
{
	if (generator != nullptr)
	{
		m_currentGraphGenerator = generator;
	}
}
