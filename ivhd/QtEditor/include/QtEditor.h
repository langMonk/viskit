#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtEditor.h"

class QtEditor : public QMainWindow
{
	Q_OBJECT

public:
	QtEditor(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtEditorClass ui;
};
