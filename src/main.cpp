#include "wnlmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WNLMainWindow w;
    w.show();
    return a.exec();
}
