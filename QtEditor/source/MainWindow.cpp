#include <QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>
#include "MainWindow.h"
#include "OpenGLRenderer.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionResetView, SIGNAL(triggered()), this, SLOT(calculateBoundingBox()));
    connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(loadDataset()));
    connect(ui.actionLoadFromDisk, SIGNAL(triggered()), this, SLOT(loadGraphFromDisk()));
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(exitEditor()));

	setupIVHD();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	m_renderer->keyPressEvent(event);
}

void MainWindow::setupIVHD()
{
	auto handler = [&](viskit::LogLevel level, const std::string& message)
	{
		switch (level)
		{
		case viskit::LogLevel::Info: ui.textBrowser_log->append("Info: " + QString::fromStdString(message)); break;
		case viskit::LogLevel::Warning: ui.textBrowser_log->append("Warning: " + QString::fromStdString(message)); break;
		case viskit::LogLevel::Error: ui.textBrowser_log->append("Error: " + QString::fromStdString(message)); break;
		default: ;
		}
	};

	// create IVHD
	m_viskit = viskit::createVisKit(handler);
	initializeIVHDResources();
	initializeEditorElements();
}

void MainWindow::initializeIVHDResources()
{

	// create particle system and graph
	m_particleSystem = m_viskit->resourceFactory().createParticleSystem();
	m_graph = m_viskit->resourceFactory().createGraph();

    // create collections
	m_casters = std::make_shared<viskit::ResourceCollection<viskit::ICaster>>();
    m_generators = std::make_shared<viskit::ResourceCollection<viskit::IGraphGenerator>>();


	// add resources to collections
	const auto casterRandom = m_viskit->resourceFactory().createCaster(viskit::CasterType::Random, viskit::OptimizerType::None);
	const auto casterMomentum = m_viskit->resourceFactory().createCaster(viskit::CasterType::IVHD, viskit::OptimizerType::Momentum);
	const auto casterForceDirected = m_viskit->resourceFactory().createCaster(viskit::CasterType::IVHD, viskit::OptimizerType::ForceDirected);
	const auto casterAdadelta = m_viskit->resourceFactory().createCaster(viskit::CasterType::IVHD, viskit::OptimizerType::Adadelta);
	const auto casterAdam = m_viskit->resourceFactory().createCaster(viskit::CasterType::IVHD, viskit::OptimizerType::Adam);
	const auto casterNesterov = m_viskit->resourceFactory().createCaster(viskit::CasterType::IVHD, viskit::OptimizerType::Nesterov);

	m_casters->add("Random", casterRandom);
	m_casters->add("Momentum", casterMomentum);
	m_casters->add("Force Directed", casterForceDirected);
	m_casters->add("Adadelta", casterAdadelta);
	m_casters->add("Adam", casterAdam);
	m_casters->add("Nesterov", casterNesterov);

	const auto bruteGenerator = m_viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::BruteForce);
    const auto faissGenerator = m_viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::Faiss);

    m_randomGenerator = m_viskit->resourceFactory().createGraphGenerator(viskit::GraphGeneratorType::Random);
    m_generators->add("Brute Force", bruteGenerator);
    if(faissGenerator != nullptr){ m_generators->add("Faiss", faissGenerator); }

    m_metricCalculator = m_viskit->resourceFactory().createMetricCalculator();

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

void MainWindow::loadDataset()
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
		auto parser = m_viskit->resourceFactory().createParser(viskit::ParserType::Csv);
		parser->loadFile(fileName.toUtf8().constData(), *m_particleSystem);
	}

	m_casters->find("Random")->calculatePositions(*m_particleSystem);

	m_renderer = new OpenGLRenderer();
	setCentralWidget(m_renderer);
}

void MainWindow::exitEditor()
{
	close();
}

[[maybe_unused]] void MainWindow::on_pushButton_CastingRun_clicked()
{
	if (m_currentCaster != nullptr)
	{
        m_currentCaster->initialize(*m_particleSystem, *m_graph);
        m_viskit->subscribeOnCastingStepFinish([&]{});

        m_running = true;
        m_castingThread = std::thread([&]()
        {
          while (m_running)
          {
              m_viskit->computeCastingStep(*m_particleSystem, *m_graph,
                                           *m_currentCaster);
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
        m_running = false;
        m_currentCaster->finalize();
	}
}

[[maybe_unused]] void MainWindow::on_pushButton_GraphGenerate_clicked()
{
	if (m_currentGraphGenerator != nullptr)
	{
        m_currentGraphGenerator->generate(*m_particleSystem, *m_graph, 2, true);
        m_randomGenerator->generate(*m_particleSystem, *m_graph, 1, true);
        m_graph->saveToCache(R"(./mnist.knn)");
	}
	else
	{

	}
}

[[maybe_unused]] void MainWindow::on_pushButton_One2many_clicked()
{

    QMessageBox::StandardButton cosine_metric;
    cosine_metric = QMessageBox::question(this, "Metric", "Use cosine metric for original data?",
                                          QMessageBox::Yes | QMessageBox::No);

//    QWidget *parent, const QString &title, const QString &label, int value = 0,
//    int minValue = -2147483647, int maxValue = 2147483647,
//    int step = 1, bool *ok = nullptr, Qt::WindowFlags flags = Qt::WindowFlags()
//

    bool ok;
    int k = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                 tr("Value of k (nearest neighbors) for which calculate the neighborhood metric:")
                                 , 1, 0, 1000, 1, &ok);
    if (ok)
        calculateMetric(k);
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

void MainWindow::setCurrentCaster(const std::shared_ptr<viskit::ICaster>& caster)
{
 	if (caster != nullptr)
	{
		m_currentCaster = caster;
	}
}

void MainWindow::setCurrentGraphGenerator(const std::shared_ptr<viskit::IGraphGenerator>& generator)
{
	if (generator != nullptr)
	{
		m_currentGraphGenerator = generator;
	}
}

void MainWindow::loadGraphFromDisk()
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
    m_randomGenerator->generate(*m_particleSystem, *m_graph, 1, true);
}

float MainWindow::calculateMetric(int k)
{
    return m_metricCalculator->calculate(*m_particleSystem, k);
}
