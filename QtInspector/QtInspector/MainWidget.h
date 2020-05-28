#pragma once

#include <QWidget>
#include "ui_MainWidget.h"

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = Q_NULLPTR);
	~MainWidget();

private:
	Ui::MainWidget ui;
};
