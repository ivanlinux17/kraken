#include "kraken.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kraken w;
    w.show();

    return a.exec();
}
