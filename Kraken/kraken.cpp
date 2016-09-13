#include "kraken.h"
#include "ui_kraken.h"

Kraken::Kraken(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kraken)
{
    ui->setupUi(this);
}

Kraken::~Kraken()
{
    delete ui;
}
