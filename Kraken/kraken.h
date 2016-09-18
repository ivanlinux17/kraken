/*! \mainpage Kraken
 * @author Ivan Lopez <ivanlinux@gmail.com>
 *
 * \section sec Introduction
 *
 * When the Kraken is released is already too late for everybody.
 * <img src="../../pics/miniKraken.jpg" align="RIGHT"></img>
 * <br> <br> <br> <br> <br>
 */

#ifndef KRAKEN_H
#define KRAKEN_H

#include <QMainWindow>
#include <QSettings>
#include <iostream>
#include <vector>

struct logType
{
    int type;
    QString message;
};

namespace Ui {
class Kraken;
}

/**
* @brief Main class that includes all the GUI elements.
*
* This class is responsible for dealing with the final user.
*/
class Kraken : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kraken(QWidget *parent = 0);
    ~Kraken();


private slots:
    void on_actionExit_triggered();

    void on_actionManual_triggered();

    void on_pushButton_clicked();

    void on_timer();

    void on_clearButton_clicked();

    void on_traceCheck_stateChanged(int arg1);

    void on_stopButton_clicked();

    void on_errorsCheck_stateChanged(int arg1);

    void on_pushButton_2_clicked();

public slots:
    void Closing();

private:
    Ui::Kraken *ui;
    std::vector<logType> log;
    QString loggingtext;
    QStringList lines;
    void Initialize();
    void filterLog ();

    QSettings *settings;


    QTimer *timerLogging;
};

#endif // KRAKEN_H
