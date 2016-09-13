#include "kraken.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Kraken window;
    window.show();
    QObject::connect(&app, SIGNAL(aboutToQuit()), &window, SLOT(Closing()));
    return app.exec();
}
