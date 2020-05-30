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

	void readJson(QString fileName);

	INode parseJson(QString data);

	void iterateObject(QJsonObject object);

	void iterateArray(QJsonArray array);
private slots:
	void OnClick();
private:
    Ui::QtInspectorClass ui;
};
