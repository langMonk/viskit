#pragma once

#include <QtWidgets/QMainWindow>
#include <ivhd/InteractiveVizualizationBuilder.h>
#include <ivhd/IResourceFactory.h>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
	void on_pushButton_Open_clicked();
	void on_pushButton_Exit_clicked();

private:
	Ui::MainWindow ui;
	std::shared_ptr<ivhd::IInteractiveVizualization> m_ext_ivhd;
};
