#pragma once

#include <QtWidgets/QMainWindow>
#include "dataTypes.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ui_QtInspector.h"

class QtInspector : public QMainWindow
{
    Q_OBJECT

public:
    QtInspector(QWidget *parent = Q_NULLPTR);

	void readJson(const QString fileName);
private slots:
	void OnClick();
private:
	class TreeModel* tModel;
    Ui::QtInspectorClass ui;
};
