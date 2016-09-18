#include "kraken.h"
#include "ui_kraken.h"

#include <QDesktopServices>
#include <QFileInfo>
#include <QtCore>
#include <QMessageBox>


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
    timerLogging = new QTimer(this);
    // Initial values
    ui->ageSpin->setRange(settings->value("minAge",0).toInt(),
                          settings->value("maxAge",130).toInt());
    ui->ageSlider->setRange(settings->value("minAge",0).toInt(),
                            settings->value("maxAge",130).toInt());
    QPixmap image("../pics/miniKraken.jpg");
    ui->pictureLabel->setPixmap(image);
    connect(timerLogging, SIGNAL(timeout()), this, SLOT(on_timer()));


    // Connecting new way
    QObject::connect (ui->ageSpin, static_cast<void (QSpinBox::*)(int)> (&QSpinBox::valueChanged),
                      ui->ageSlider, &QSlider::setValue);
    // Connecting old way
    QObject::connect (ui->ageSlider, SIGNAL(valueChanged(int)), ui->ageSpin, SLOT(setValue(int)));



    ui->ageSpin->setValue(settings->value("lastAge",35).toInt());
    timerLogging->start(100);
    ui->logEdit->setMaximumBlockCount(80);
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

void Kraken::on_actionManual_triggered()
{
    //QDesktopServices::openUrl(QUrl("file:///C:/Documents and Settings/All Users/Desktop", QUrl::TolerantMode));
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo("../docs/html/index.html").absoluteFilePath()));
}

void Kraken::on_pushButton_clicked()
{
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    QString searchKey = ui->searchKeyEdit->text();
}

void Kraken::on_timer()
{
    QString text;
    int value = qrand() % 10;
    if (value <= 2)
    {
        text = QString("<font color=\"red\">18/12 Error Oh my god! An error ocurred</font>");
        if (ui->errorsCheck->isChecked())
            ui->logEdit->appendHtml(text);
    }
    else
    {
        text = QString ("18/12 Trace The value returned from the function was %1")
                .arg(value);
        if (ui->traceCheck->isChecked())
            ui->logEdit->appendHtml(text);
    }
    this->lines.append(text);
    if (lines.count()>80)
        lines.pop_front();

    QString mess = QString ("lines size %1 logedit size %2.")
                           .arg(lines.count()).arg(ui->logEdit->blockCount());
    std::cout<<mess.toStdString()<<std::endl;
}

void Kraken::on_clearButton_clicked()
{
    ui->logEdit->clear();
}
void Kraken::filterLog()
{
    ui->logEdit->clear();

    for (int i = 0; i < lines.size();i++)
    {
        QString line = lines[i];
        if (line.contains("Error") && ui->errorsCheck->isChecked())
            ui->logEdit->appendHtml(line);
        else
        {
            if (line.contains("Trace") && ui->traceCheck->isChecked())
                ui->logEdit->appendHtml(line);
        }
    }
}

void Kraken::on_traceCheck_stateChanged(int)
{
    filterLog();
}

void Kraken::on_stopButton_clicked()
{
    this->timerLogging->stop();
}


void Kraken::on_errorsCheck_stateChanged(int)
{
    filterLog();
}

void Kraken::on_pushButton_2_clicked()
{
    timerLogging->start();
}
