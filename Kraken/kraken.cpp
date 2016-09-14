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

/**
* @brief Initialize all the GUI components.
*/
void Kraken::Initialize()
{
    // Read Ini
    settings = new QSettings("../kraken.ini", QSettings::IniFormat);
    // Initial values
    ui->ageSpin->setRange(settings->value("minAge",0).toInt(),
                          settings->value("maxAge",130).toInt());
    ui->ageSlider->setRange(settings->value("minAge",0).toInt(),
                            settings->value("maxAge",130).toInt());
    QPixmap image("../pics/miniKraken.jpg");
    ui->pictureLabel->setPixmap(image);

    // Connecting new way
    QObject::connect (ui->ageSpin, static_cast<void (QSpinBox::*)(int)> (&QSpinBox::valueChanged),
                      ui->ageSlider, &QSlider::setValue);
    // Connecting old way
    QObject::connect (ui->ageSlider, SIGNAL(valueChanged(int)), ui->ageSpin, SLOT(setValue(int)));



    ui->ageSpin->setValue(settings->value("lastAge",35).toInt());
}

/**
* @brief Saves the status of some widgets for the next time.
*/
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
