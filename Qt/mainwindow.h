/*
 * IHM_REV2: mainwindow.h
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "constants.h"
#include "protocol.h"
#include "protocolwindow.h"
#include "ui_mainwindow.h"
#include "rs232.h"
#include <QCoreApplication>
#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool paused;
    unsigned int load;
    unsigned int old_load;
    unsigned int selection;
    QTime time;
    QTimer* timer_com;
    QTimer* timer_seconds;
    protocol_t protocol;
    protocolwindow* protocolw;
    database_t database;
    savefileparser_t saveFileParser;
    unsigned char buf[SERIAL_BUFFER_LENGTH];
    QString bufStr;
    unsigned int rpm;
    float torque;
    //QFile* logFile;

    void sendLoad(unsigned int);
    void parseSerial(int);
    void serialErrorHandler();

private slots:
    void on_pb_increaseLoad_clicked();
    void on_pb_decreaseLoad_clicked();
    void on_pb_play_clicked();
    void on_pb_stop_clicked();
    void on_pb_pause_clicked();
    void on_pb_protocol_clicked();
    void on_pb_manual_clicked();
    void timer_seconds_timeout();
    void timer_com_timeout();
    void widget_destroyed();
};

#endif // MAINWINDOW_H
