#ifndef KRAKEN_H
#define KRAKEN_H

#include <QMainWindow>

namespace Ui {
class Kraken;
}

class Kraken : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kraken(QWidget *parent = 0);
    ~Kraken();

private:
    Ui::Kraken *ui;
};

#endif // KRAKEN_H
