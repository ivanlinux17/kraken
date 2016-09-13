#include "kraken.h"
#include "ui_kraken.h"


Kraken::Kraken(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kraken)
{
    ui->setupUi(this);
    QSettings settings ("kraken.ini", QSettings::IniFormat);

    Initialize();
}

Kraken::~Kraken()
{
    delete ui;
}

void Kraken::Initialize()
{
    // Read Ini
    settings = new QSettings("../kraken.ini", QSettings::IniFormat);
    // Initial values
    ui->ageSpin->setRange(settings->value("minAge",0).toInt(),settings->value("maxAge",130).toInt());
    ui->ageSlider->setRange(settings->value("minAge",0).toInt(),settings->value("maxAge",130).toInt());
    QPixmap image("../pics/miniKraken.jpg");
    ui->pictureLabel->setPixmap(image);

    // Connecting
    QObject::connect (ui->ageSpin, SIGNAL(valueChanged(int)), ui->ageSlider, SLOT(setValue(int)));
    QObject::connect (ui->ageSlider, SIGNAL(valueChanged(int)), ui->ageSpin, SLOT(setValue(int)));



    ui->ageSpin->setValue(settings->value("lastAge",35).toInt());
}
void Kraken::Closing()
{
    settings->setValue("lastAge",ui->ageSlider->value());
    settings->sync();
}

void Kraken::on_actionExit_triggered()
{
    Closing();
    QApplication::quit();
}