#include <QFileDialog>
#include <QDesktopServices>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void MainWindow::on_pushButton_Open_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Choose dataset"), "",
		tr("CSV format(*.csv);;All Files (*)"));

	if (fileName.isEmpty())
	{
		return;
	}
	else
	{

	}
}

void MainWindow::on_pushButton_Exit_clicked()
{
	close();
}