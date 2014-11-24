#include "pingerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PingerWindow w;
    w.show();

    return a.exec();
}
