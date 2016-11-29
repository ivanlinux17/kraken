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
    QObject::connect (ui->ageSpin, static_cast<void (QSpinBox::*)(int)>
                     (&QSpinBox::valueChanged), ui->ageSlider,
                     &QSlider::setValue);
    // Connecting old way
    QObject::connect (ui->ageSlider, SIGNAL(valueChanged(int)), ui->ageSpin, SLOT(setValue(int)));



    ui->ageSpin->setValue(settings->value("lastAge",35).toInt());
    timerLogging->start(100);
    //ui->logEdit->setMaximumBlockCount(80);
    ui->logEdit->document()->setMaximumBlockCount(80);
}

/**
* @brief Saves the status of some widgets for the next time.
*/
void Kraken::Closing()
{
    settings->setValue("lastAge",ui->ageSlider->value());
    settings->sync();
}

void Kraken::HighLightWord(QTextCursor cursor)
{
    QTextCharFormat plainFormat(cursor.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setBackground(Qt::blue);
    std::cout << cursor.blockNumber()<< "   " << cursor.columnNumber() << " ";
    cursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
    std::cout << cursor.columnNumber() << std::endl;
    cursor.mergeCharFormat(colorFormat);
    ui->logEdit->setTextCursor(cursor);
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

void Kraken::on_searchButton_clicked()
{
    key = ui->searchKeyEdit->text();
    ui->prevButton->setEnabled(true);
    ui->nextButton->setEnabled(true);

    /*QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection extra;
    ui->logEdit->moveCursor(QTextCursor::Start);

    //QTextCharFormat plainFormat(highlightCursor.charFormat());
    QTextCharFormat colorFormat;
    colorFormat.setForeground(Qt::red);
    while (ui->logEdit->find(key))
    {
        extra.cursor = ui->logEdit->textCursor();
        extra.cursor.mergeCharFormat(colorFormat);
        extraSelections.append(extra);
    }

    ui->logEdit->setExtraSelections(extraSelections);
    */
    QRegExp regex = QRegExp(ui->searchKeyEdit->text());
    posInSearch = 0;
   /* cursorSearch = ui->logEdit->
    if (regex.indexIn(self.toPlainText(), posInSearch) > 0)
    {

    }*/


    ui->logEdit->moveCursor(QTextCursor::Start);
    logText = ui->logEdit->document();

    cursor = QTextCursor (logText);
    this->on_nextButton_clicked();
    /*while (ui->logEdit->find(key))
    {
        cursorAtWord.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
        cursorAtWord.mergeCharFormat(colorFormat);
    }*/
}

void Kraken::on_timer()
{
    QString text;
    int value = qrand() % 10;
    if (value <= 2)
    {
        text = QString("<font color=\"red\">18/12 Error Oh my god! An error ocurred</font>");
        if (ui->errorsCheck->isChecked())
            //ui->logEdit->appendHtml(text);
            ui->logEdit->append(text);
    }
    else
    {
        text = QString ("18/12 Trace The value returned from the function was %1")
                .arg(value);
        if (ui->traceCheck->isChecked())
            //ui->logEdit->appendHtml(text);
            ui->logEdit->append(text);
    }
    this->lines.append(text);
    if (lines.count()>80)
        lines.pop_front();

    QString mess = QString ("lines size %1 logedit size %2.")
                           .arg(lines.count()).arg(ui->logEdit->document()->blockCount());
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
            //ui->logEdit->appendHtml(line);
            ui->logEdit->append(line);
        else
        {
            if (line.contains("Trace") && ui->traceCheck->isChecked())
                //ui->logEdit->appendHtml(line);
                ui->logEdit->append(line);
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

void Kraken::on_nextButton_clicked()
{
    cursor = logText->find(key,cursor);
    if (!cursor.isNull())
    {
        //ui->nextButton->setEnabled(true);
        this->HighLightWord(cursor);

    }
    else
        ui->nextButton->setEnabled(false);

}


void Kraken::on_prevButton_clicked()
{
    cursor = logText->find(key,cursor,QTextDocument::FindBackward);
    if (!cursor.isNull())
    {
        //ui->prevButton->setEnabled(false);
        this->HighLightWord(cursor);
    }
    else
        ui->prevButton->setEnabled(true);
}
