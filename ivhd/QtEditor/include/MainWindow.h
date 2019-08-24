#pragma once
 
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <ivhd/InteractiveVizualizationBuilder.h>
#include <ivhd/IParser.h>
#include <ivhd/ICaster.h>
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

	std::shared_ptr<ivhd::IParticleSystem> particleSystem() { return m_ivhd_particleSystem; }

private:
	MainWindow(QWidget* parent = Q_NULLPTR);
	void keyPressEvent(QKeyEvent* event) override;
	void createIVHD();

private slots:
	void on_pushButton_Open_clicked();
	void on_pushButton_Exit_clicked();
	void on_pushButton_CastingRun();

private:
	Ui::MainWindow ui;
	std::shared_ptr<ivhd::IInteractiveVizualization> m_ivhd;
	std::shared_ptr<ivhd::IParticleSystem> m_ivhd_particleSystem;
	OpenGLRenderer* m_renderer;
};