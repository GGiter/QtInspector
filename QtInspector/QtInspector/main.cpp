#include "QtInspector.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QFile File("QTDark.stylesheet");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	a.setWindowIcon(QIcon(":/QtInspector/Resources/object_icon.png"));
	a.setStyleSheet(StyleSheet);
    QtInspector w;
    w.show();
    return a.exec();
}
