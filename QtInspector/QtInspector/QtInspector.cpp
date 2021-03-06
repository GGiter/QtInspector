#include "QtInspector.h"
#include <QFile>
#include "Reader.h"
#include <QDebug>
#include <QPushButton>
#include <fstream>
#include "TreeModel.h"
#include "Delegate.h"

QtInspector::QtInspector(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &QtInspector::OnClick);
	tModel = new TreeModel(this);
	ui.treeView->setModel(tModel);
	TestDelegate* testDelegate = new TestDelegate(ui.treeView);

	ui.treeView->setItemDelegate(testDelegate);
}

void QtInspector::readJson(const QString fileName)
{
	Reader reader;
	INode* root = reader.parse_file(fileName.toStdString());
	
	tModel->root = root;
	tModel->reset();	
	ui.treeView->update();
}
void QtInspector::OnClick()
{
	readJson("test.json");
}