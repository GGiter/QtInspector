#include "QtInspector.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtInspector w;
    w.show();
    return a.exec();
}
