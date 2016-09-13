#ifndef KRAKEN_H
#define KRAKEN_H

#include <QMainWindow>
#include <QSettings>
#include <iostream>

namespace Ui {
class Kraken;
}

class Kraken : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kraken(QWidget *parent = 0);
    ~Kraken();


private slots:
    void on_actionExit_triggered();

public slots:
    void Closing();

private:
    Ui::Kraken *ui;
    void Initialize();

    QSettings *settings;
};

#endif // KRAKEN_H
