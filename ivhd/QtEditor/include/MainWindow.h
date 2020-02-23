#pragma once

#include <ivhd/InteractiveVizualizationBuilder.h>
#include <ivhd/IParser.h>
#include <ivhd/ICaster.h>
#include <ivhd/IGraphGenerator.h>
#include <ivhd/IGraph.h>
#include <ivhd/IResourceCollection.h>
#include <ivhd/IResourceFactory.h>
#include <ivhd/IParticleSystem.h>

#include "ui_MainWindow.h"

class OpenGLRenderer;

class MainWindow : public QMainWindow
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

	[[nodiscard]] ivhd::IParticleSystem& particleSystem() const { return *m_particleSystem.get(); }

	void setCurrentCaster(std::shared_ptr<ivhd::ICaster> caster);
	void setCurrentGraphGenerator(std::shared_ptr<ivhd::IGraphGenerator> generator);

private:
	MainWindow(QWidget* parent = Q_NULLPTR);
	void keyPressEvent(QKeyEvent* event) override;
	
	void setupIVHD();
	void initializeIVHDResources();
	void initializeEditorElements();
	
private slots:
	void on_pushButton_Open_clicked();
	void on_pushButton_Exit_clicked();
	void on_pushButton_CastingRun_clicked();
	void on_pushButton_CastingStop_clicked();
	void on_pushButton_GraphRun_clicked() const;
	void on_comboBox_CastingSetup_activated();
	void on_comboBox_GraphSetup_activated();
	void on_actionReset_View_clicked();
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
	
	std::shared_ptr<ivhd::IInteractiveVizualization> m_ivhd;

	// IVHD collections and current resources
	std::shared_ptr<ivhd::IResourceCollection<ivhd::ICaster>> m_casters;
	std::shared_ptr<ivhd::IResourceCollection<ivhd::IGraphGenerator>> m_generators;

	std::shared_ptr<ivhd::ICaster> m_currentCaster{ nullptr };
	std::shared_ptr<ivhd::IGraphGenerator> m_currentGraphGenerator{ nullptr };
	std::shared_ptr<ivhd::IParticleSystem> m_particleSystem{ nullptr };
	std::shared_ptr<ivhd::IGraph> m_graph{ nullptr };

};
