#pragma once

#include <QtWidgets/QMainWindow>
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
};
