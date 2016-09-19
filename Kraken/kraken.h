/*! \mainpage Kraken
 * @author Ivan Lopez <ivanlinux@gmail.com>
 *
 * \section Introduction
 * This tool has been created for learning how to develop
 * a powerful GUI. And, please, always remember:
 * > When the Kraken is released is already too late for everybody.
 *
 * \section QT
 * There are different libraries available:
 * * GTK
 * * MSVS (WPF)
 * * TK/Int
 *
 * However QT is cross-platform, very mature library with a huge collection
 * of classes that ease the creation of GUI tools.
 *
 *
 * - Timer
 * --------
 * Using this class, a function could be called every X milliseconds.
 * ~~~~~~~~~~~~~~~{.c}
 * QTimmer timerLogging = QTimmer (this);
 * timerLogging.start(100);
 * connect(timerLogging, SIGNAL(timeout()), this, SLOT(on_timer()));
 * ~~~~~~~~~~~~~~~
 *
 * - QPlainText
 * -------------
 * @code{.c}
 * QTimmer timerLogging = QTimmer (this);
 * timerLogging.start(100);
 * connect(timerLogging, SIGNAL(timeout()), this, SLOT(on_timer()));
 * @endcode
 *
 *
 * <img src="../../pics/miniKraken.jpg" align="RIGHT"></img>
 * <br> <br> <br> <br> <br>
 */

#ifndef KRAKEN_H
#define KRAKEN_H

#include <QMainWindow>
#include <QSettings>
#include <iostream>
#include <vector>

#include <QDesktopServices>
#include <QFileInfo>
#include <QtCore>
#include <QMessageBox>
#include <QTextCursor>
#include <QRegExp>

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

    void on_searchButton_clicked();

    void on_timer();

    void on_clearButton_clicked();

    void on_traceCheck_stateChanged(int arg1);

    void on_stopButton_clicked();

    void on_errorsCheck_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_nextButton_clicked();

    void on_prevButton_clicked();

public slots:
    void Closing();

private:
    Ui::Kraken *ui;
    std::vector<logType> log;
    QString loggingtext;
    QStringList lines;
    QString key;
    int posInSearch;
    QTextDocument* logText;
    QTextCursor cursor;
    QTextCursor cursorSearch;
    void Initialize();
    void filterLog ();
    void HighLightWord(QTextCursor cursor);

    QSettings *settings;


    QTimer *timerLogging;
};

#endif // KRAKEN_H
