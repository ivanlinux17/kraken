#include "kraken.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Kraken window;
    window.show();
    QObject::connect(&app, &QApplication::aboutToQuit, &window, &Kraken::Closing);
    return app.exec();
}
