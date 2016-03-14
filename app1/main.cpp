#include "maindialog.h"
#include <QtGui/QApplication>

int main(int arc, char **argv)
{
    QApplication a(arc, argv);

    MainDialog dlg;
    dlg.show();

    return a.exec();
}
