#pragma once
 
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <ivhd/InteractiveVizualizationBuilder.h>
#include <ivhd/IParser.h>
#include <ivhd/ICaster.h>
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

	ivhd::IParticleSystem& particleSystem() const { return m_ivhd->particleSystem(); }
	
	void setCurrentCaster(std::shared_ptr<ivhd::ICaster> caster);

private:
	MainWindow(QWidget* parent = Q_NULLPTR);
	void keyPressEvent(QKeyEvent* event) override;
	void setupIVHD();

private slots:
	void on_pushButton_Open_clicked();
	void on_pushButton_Exit_clicked();
	void on_pushButton_CastingRun_clicked();

	// Qt resources
private:
	Ui::MainWindow ui;
	OpenGLRenderer* m_renderer{ nullptr };

	// IVHD resources
private:
	std::shared_ptr<ivhd::IInteractiveVizualization> m_ivhd;

	// IVHD collections and current resources
	std::shared_ptr<ivhd::IResourceCollection<ivhd::ICaster>> m_casters;
	std::shared_ptr<ivhd::ICaster> m_currentCaster;
};