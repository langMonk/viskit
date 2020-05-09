#pragma once

#include <InteractiveVisualizationBuilder.h>
#include <IParser.h>
#include <ICaster.h>
#include <IGraphGenerator.h>
#include <IGraph.h>
#include <ResourceCollection.h>
#include <IResourceFactory.h>
#include <IParticleSystem.h>

#include <IGpuFactory.h>

#include <QMainWindow>
#include "ui_MainWindow.h"



class OpenGLRenderer;

class MainWindow final : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(MainWindow const&) = delete;
	MainWindow& operator=(MainWindow const&) = delete;

	static std::shared_ptr<MainWindow> instance()
	{
		static std::shared_ptr<MainWindow> s{ new MainWindow };
		return s;
	}

	[[nodiscard]] ivhd::IParticleSystem& particleSystem() const { return *m_particleSystem; }

	void setCurrentCaster(std::shared_ptr<ivhd::ICaster> caster);
	void setCurrentGraphGenerator(std::shared_ptr<ivhd::IGraphGenerator> generator);

private:
	explicit MainWindow(QWidget* parent = Q_NULLPTR);
	void keyPressEvent(QKeyEvent* event) override;
	
	void setupIVHD();
	void initializeIVHDResources();
	void initializeEditorElements();
	
private slots:

    [[maybe_unused]] void on_pushButton_Open_clicked();
    [[maybe_unused]] void on_pushButton_Exit_clicked();
    [[maybe_unused]] void on_pushButton_CastingRun_clicked();
    [[maybe_unused]] void on_pushButton_CastingStop_clicked();
    [[maybe_unused]] void on_pushButton_GraphGenerate_clicked();
    [[maybe_unused]] void on_comboBox_CastingSetup_activated();
    [[maybe_unused]] void on_comboBox_GraphSetup_activated();
    [[maybe_unused]] void on_actionReset_View_clicked();
    [[maybe_unused]] void on_pushButton_GraphOpen_clicked();
	void calculateBoundingBox();

	// Qt resources
private:
	Ui::MainWindow ui;
	OpenGLRenderer* m_renderer{ nullptr };

	bool m_running{ false };

	// IVHD resources
private:
	glm::vec4 bounding_box_min;
	glm::vec4 bounding_box_max;
	
	std::shared_ptr<ivhd::IInteractiveVisualization> m_ivhd;
    std::shared_ptr<ivhd::cuda::IGpuFactory> m_gpuFactory;

	// IVHD collections and current resources
	std::shared_ptr<ivhd::ResourceCollection<ivhd::ICaster>> m_casters;
	std::shared_ptr<ivhd::ResourceCollection<ivhd::IGraphGenerator>> m_generators;

	std::shared_ptr<ivhd::ICaster> m_currentCaster{ nullptr };
	std::shared_ptr<ivhd::IGraphGenerator> m_currentGraphGenerator{ nullptr };
	std::shared_ptr<ivhd::IParticleSystem> m_particleSystem{ nullptr };
	std::shared_ptr<ivhd::IGraph> m_graph{ nullptr };

};
