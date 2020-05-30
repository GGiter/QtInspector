#include "QtInspector.h"
#include <QFile>
#include "Reader.h"
#include <QDebug>
#include <QPushButton>
#include <fstream>

QtInspector::QtInspector(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &QtInspector::OnClick);
}

void QtInspector::readJson(QString fileName)
{
	Reader reader;
	INode* root = reader.parse_file("test.json");
	qDebug() << "Reading";
	qDebug() << root->getKey();
	qDebug() << root->size();
	if (root->getType() == dataType::object)
	{
		qDebug() << "Object";
	}


	delete root;
	
}
INode QtInspector::parseJson(QString data)
{
	return INode();
}
void QtInspector::iterateObject(QJsonObject object)
{
	qDebug() << object;
	for (auto item : object)
	{
		if (item.isObject())
		{
			iterateObject(item.toObject());
		}
		else if (item.isArray())
		{
			iterateArray(item.toArray());

		}
		else
		{
			qDebug() << item.toString();
		}
	}
}

void QtInspector::iterateArray(QJsonArray array)
{
	qDebug() << array;
	for (auto item : array)
	{
		if (item.isObject())
		{
			iterateObject(item.toObject());
		}
		else if (item.isArray())
		{
			iterateArray(item.toArray());

		}
		else
		{	
			qDebug() << item.toString();
		}
	}

}
void QtInspector::OnClick()
{
	readJson("test.json");
}