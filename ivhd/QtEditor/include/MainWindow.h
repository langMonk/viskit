#pragma once
 
#include <QtWidgets/QMainWindow>
#include <ivhd/InteractiveVizualizationBuilder.h>
#include <ivhd/IResourceFactory.h>
#include <ivhd/IParticleSystem.h>

#include "ui_MainWindow.h"

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

	std::shared_ptr<ivhd::IInteractiveVizualization> interactiveVizualization() { return m_ext_ivhd; }

private:
	MainWindow(QWidget* parent = Q_NULLPTR);

private slots:
	void on_pushButton_Open_clicked();
	void on_pushButton_Exit_clicked();

private:
	Ui::MainWindow ui;
	std::shared_ptr<ivhd::IInteractiveVizualization> m_ext_ivhd;
  
};