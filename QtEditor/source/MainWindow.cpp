#include <QFileDialog>
#include "MainWindow.h"
#include "OpenGLRenderer.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionResetView, SIGNAL(triggered()), this, SLOT(calculateBoundingBox()));
	setupIVHD();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	m_renderer->keyPressEvent(event);
}

void MainWindow::setupIVHD()
{
	auto handler = [&](ivhd::LogLevel level, const std::string& message)
	{
		switch (level)
		{
		case ivhd::LogLevel::Info: ui.textBrowser_log->append("Info: " + QString::fromStdString(message)); break;
		case ivhd::LogLevel::Warning: ui.textBrowser_log->append("Warning: " + QString::fromStdString(message)); break;
		case ivhd::LogLevel::Error: ui.textBrowser_log->append("Error: " + QString::fromStdString(message)); break;
		default: ;
		}
	};

	// create IVHD
	m_ivhd = ivhd::createIVHD(handler);
	initializeIVHDResources();
	initializeEditorElements();
}

void MainWindow::initializeIVHDResources()
{

	// create particle system and graph
	m_particleSystem = m_ivhd->resourceFactory().createParticleSystem();
	m_graph = m_ivhd->resourceFactory().createGraph();

    // create collections
	m_casters = std::make_shared<ivhd::ResourceCollection<ivhd::ICaster>>();
    m_generators = std::make_shared<ivhd::ResourceCollection<ivhd::IGraphGenerator>>();


	// add resources to collections
	const auto casterRandom = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::Random);
	const auto casterMomentum = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::IVHD, ivhd::OptimizerType::Momentum);
	const auto casterForceDirected = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::IVHD, ivhd::OptimizerType::ForceDirected);
	const auto casterAdadelta = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::IVHD, ivhd::OptimizerType::Adadelta);
	const auto casterAdam = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::IVHD, ivhd::OptimizerType::Adam);
	const auto casterNesterov = m_ivhd->resourceFactory().createCaster(ivhd::CasterType::IVHD, ivhd::OptimizerType::Nesterov);

	m_casters->add("Random", casterRandom);
	m_casters->add("Momentum", casterMomentum);
	m_casters->add("Force Directed", casterForceDirected);
	m_casters->add("Adadelta", casterAdadelta);
	m_casters->add("Adam", casterAdam);
	m_casters->add("Nesterov", casterNesterov);

	const auto bruteGenerator = m_ivhd->resourceFactory().createGraphGenerator(ivhd::GraphGeneratorType::BruteForce);
	const auto randomGenerator = m_ivhd->resourceFactory().createGraphGenerator(ivhd::GraphGeneratorType::Random);
    const auto faissGenerator = m_ivhd->resourceFactory().createGraphGenerator(ivhd::GraphGeneratorType::Faiss);

    m_generators->add("Brute Force", bruteGenerator);
    m_generators->add("Random", randomGenerator);
    if(faissGenerator != nullptr){ m_generators->add("Faiss", faissGenerator); }


	// set default resources
	setCurrentCaster(casterRandom);
	setCurrentGraphGenerator(bruteGenerator); 
}

void MainWindow::initializeEditorElements()
{
	// casters
	m_casters->iterate([&](const std::string& name) {
		ui.comboBox_CastingSetup->addItem(QString::fromStdString(name));
	});

	// graph generators
	m_generators->iterate([&](const std::string& name) {
		ui.comboBox_GraphSetup->addItem(QString::fromStdString(name));
	});
}

[[maybe_unused]] void MainWindow::on_pushButton_Open_clicked()
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
		parser->loadFile(fileName.toUtf8().constData(), *m_particleSystem);
	}

	m_casters->find("Random")->calculatePositions(*m_particleSystem);

	m_renderer = new OpenGLRenderer();
	setCentralWidget(m_renderer);
}

[[maybe_unused]] void MainWindow::on_pushButton_Exit_clicked()
{
	close();
}

[[maybe_unused]] void MainWindow::on_pushButton_CastingRun_clicked()
{
	if (m_currentCaster != nullptr) {
        m_currentCaster->initialize(*m_particleSystem, *m_graph);
        m_running = true;

        m_castingThread = std::thread([&]() {
            while(m_running)
            {
                m_currentCaster->step(*m_particleSystem, *m_graph);
            }
        });
	}
	else
	{

	}
}

[[maybe_unused]] void MainWindow::on_pushButton_CastingStop_clicked()
{
	if(m_running)
	{
        m_castingThread.join();
        m_currentCaster->finalize();
	}

	m_running = false;
}

[[maybe_unused]] void MainWindow::on_pushButton_GraphGenerate_clicked()
{
	if (m_currentGraphGenerator != nullptr)
	{
        m_currentGraphGenerator->generate(*m_particleSystem, *m_graph, 2, true);
        m_graph->saveToCache(R"(./mnist.knn)");

	}
	else
	{

	}
}

[[maybe_unused]] void MainWindow::on_pushButton_GraphOpen_clicked()
{
	if (!m_particleSystem->empty())
	{
		m_particleSystem->clear();
	}

	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Choose knn file"), "",
		tr("knn format(*.knn);;All Files (*)"));

	if (fileName.isEmpty())
	{
		return;
	}
	
	m_graph->loadFromCache(fileName.toUtf8().constData());

	auto temp = m_currentGraphGenerator;
    setCurrentGraphGenerator(m_generators->find("Random"));
    m_currentGraphGenerator->generate(*m_particleSystem, *m_graph, 1, true);
    setCurrentGraphGenerator(temp);
}

[[maybe_unused]] void MainWindow::on_comboBox_CastingSetup_activated()
{
	setCurrentCaster(m_casters->find(ui.comboBox_CastingSetup->currentText().toStdString()));
}

[[maybe_unused]] void MainWindow::on_comboBox_GraphSetup_activated()
{
	setCurrentGraphGenerator(m_generators->find(ui.comboBox_GraphSetup->currentText().toStdString()));
}

[[maybe_unused]] void MainWindow::on_actionReset_View_clicked()
{
	calculateBoundingBox();
}

void MainWindow::calculateBoundingBox()
{
	auto positions = m_particleSystem->positions();
	const auto countParticles = m_particleSystem->countParticles();
	
	bool first = true;
	for (int i = 0; i < countParticles; i++)
	{
		if (first)
		{
			bounding_box_max = bounding_box_min = positions[i];
			first = false;
		}
		
		if (bounding_box_min.x > positions[i].x)
			bounding_box_min.x = positions[i].x;
		if (bounding_box_max.x < positions[i].x)
			bounding_box_max.x = positions[i].x;

		if (bounding_box_min.y > positions[i].y)
			bounding_box_min.y = positions[i].y;
		if (bounding_box_max.y < positions[i].y)
			bounding_box_max.y = positions[i].y;
	}

	m_renderer->setBoundingBox(bounding_box_min, bounding_box_max);
}

void MainWindow::setCurrentCaster(const std::shared_ptr<ivhd::ICaster>& caster)
{
 	if (caster != nullptr)
	{
		m_currentCaster = caster;
	}
}

void MainWindow::setCurrentGraphGenerator(const std::shared_ptr<ivhd::IGraphGenerator>& generator)
{
	if (generator != nullptr)
	{
		m_currentGraphGenerator = generator;
	}
}
