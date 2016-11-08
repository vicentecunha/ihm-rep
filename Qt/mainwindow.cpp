/*
 * IHM_REV2: mainwindow.cpp
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

/* =======================================================================
 * Includes
 * ======================================================================= */

#include "mainwindow.h"
#include <algorithm>

/* =======================================================================
 * Constructors and Destructors
 * ======================================================================= */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    protocol.setId(MANUAL);
    load = MINLOAD_WATTS;
    paused = false;
    time.setHMS(0,0,0);
    rpm = 0;
    torque = 0;
    bufStr = "";
    std::fill_n(buf, SERIAL_BUFFER_LENGTH, 0);

    timer_seconds = new QTimer(this);
    timer_com = new QTimer(this);
    connect(timer_seconds, SIGNAL(timeout()), this, SLOT(timer_seconds_timeout()));
    connect(timer_com, SIGNAL(timeout()), this, SLOT(timer_com_timeout()));

    ui->pb_stop->setEnabled(false);
    ui->pb_pause->setEnabled(false);
    ui->pb_manual->setEnabled(false);

    database = saveFileParser.download(SAVE_FILE);
    selection = database.getSelection();
    if (RS232_OpenComport(SERIAL_PORT_NUMBER, SERIAL_PORT_BAUDRATE, "8N1") == 1) serialErrorHandler();
    timer_com->start(100);
}

MainWindow::~MainWindow()
{
    delete timer_com;
    delete timer_seconds;
    RS232_CloseComport(SERIAL_PORT_NUMBER);
    delete ui;
}

/* =======================================================================
 * Private Functions
 * ======================================================================= */

void MainWindow::sendLoad(unsigned int load)
{
    QString loadString = QString("%1").arg(load, 3, 10, QChar('0'));
    unsigned char buffer[5];
    buffer[0] = 0xA0;
    buffer[1] = 0x00;
    memcpy((unsigned char*)(buffer+2), loadString.toStdString().c_str(), 3);
    RS232_SendBuf(SERIAL_PORT_NUMBER, buffer, 5);
}

void MainWindow::parseSerial(int len)
{
    static QString bufStr = "";

    // Extract received buffer
    for (int i = 0; i < len; i++)
    {
        if (buf[i] == 'B') bufStr = "";
        else bufStr += buf[i];
        buf[i] = '\0';
    }

    // Parse string
    if (bufStr.length() >= 3)
    {
        rpm = bufStr.left(3).toInt();
        if (rpm == 0) torque = 0;
        else
        {
            float newTorque = (float)load/(float)rpm;
            torque = (newTorque > 4) ? 4 : newTorque;
        }
    }
}

void MainWindow::serialErrorHandler()
{
    system("serialError.sh");
    exit(-1);
}

/* =======================================================================
 * Signal Handlers
 * ======================================================================= */

void MainWindow::on_pb_increaseLoad_clicked()
{
    unsigned int newLoad = ui->cb_timesFive->isChecked() ? load + 5 : load + 1;
    load = (newLoad <= MAXLOAD_WATTS) ? newLoad : load;
    ui->lbl_loadValue->setText(QString::number(load));
}

void MainWindow::on_pb_decreaseLoad_clicked()
{
    unsigned int newLoad = ui->cb_timesFive->isChecked() ? load - 5 : load - 1;
    load = (newLoad >= MINLOAD_WATTS) ? newLoad : load;
    ui->lbl_loadValue->setText(QString::number(load));
}

void MainWindow::on_pb_play_clicked()
{
    timer_seconds->start(1000);
    if (paused)
    {
        load = old_load;
        paused = false;
    }
    else if (protocol.getId() != MANUAL)
    {
        load = protocol.getStage(1).getLoad();
    }
    ui->lbl_loadValue->setText(QString::number(load));

    ui->pb_play->setEnabled(false);
    ui->pb_stop->setEnabled(true);
    ui->pb_pause->setEnabled(true);
    ui->pb_protocol->setEnabled(false);

    if (protocol.getId() == MANUAL)
    {
        ui->pb_increaseLoad->setEnabled(true);
        ui->pb_decreaseLoad->setEnabled(true);
    }
    else
    {
        ui->pb_increaseLoad->setEnabled(false);
        ui->pb_decreaseLoad->setEnabled(false);
    }
}

void MainWindow::on_pb_stop_clicked()
{
    timer_seconds->stop();
    paused = false;
    time.setHMS(0,0,0);
    ui->lbl_timeValue->setText(time.toString("hh:mm:ss"));
    load = MINLOAD_WATTS;
    ui->lbl_loadValue->setText(QString::number(load));

    rpm = 0;
    torque = 0;
    ui->lbl_frequencyValue->setText(QString::number(rpm));
    ui->lbl_torqueValue->setText(QString::number(torque, 'f', 2));

    ui->pb_play->setEnabled(true);
    ui->pb_stop->setEnabled(false);
    ui->pb_pause->setEnabled(false);
    ui->pb_protocol->setEnabled(true);

    if (protocol.getId() == MANUAL)
    {
        ui->pb_increaseLoad->setEnabled(true);
        ui->pb_decreaseLoad->setEnabled(true);
    }
    else
    {
        ui->pb_increaseLoad->setEnabled(false);
        ui->pb_decreaseLoad->setEnabled(false);
    }
}

void MainWindow::on_pb_pause_clicked()
{
    timer_seconds->stop();
    paused = true;
    old_load = load;
    // Reset load:
    /*
    load = MINLOAD_WATTS;
    ui->lbl_loadValue->setText(QString::number(load));
    */

    rpm = 0;
    torque = 0;
    ui->lbl_frequencyValue->setText(QString::number(rpm));
    ui->lbl_torqueValue->setText(QString::number(torque, 'f', 2));

    ui->pb_play->setEnabled(true);
    ui->pb_stop->setEnabled(true);
    ui->pb_pause->setEnabled(false);
    ui->pb_protocol->setEnabled(false);

    if (protocol.getId() == MANUAL)
    {
        ui->pb_increaseLoad->setEnabled(true);
        ui->pb_decreaseLoad->setEnabled(true);
    }
    else
    {
        ui->pb_increaseLoad->setEnabled(false);
        ui->pb_decreaseLoad->setEnabled(false);
    }
}

void MainWindow::on_pb_protocol_clicked()
{
    protocolw = new protocolwindow();
    protocolw->setAttribute(Qt::WA_DeleteOnClose);
    connect(protocolw, SIGNAL(destroyed()), this, SLOT(widget_destroyed()));
    protocolw->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    protocolw->show();
}

void MainWindow::on_pb_manual_clicked()
{
    protocol.setId(MANUAL);
    ui->pb_manual->setEnabled(false);
    ui->pb_increaseLoad->setEnabled(true);
    ui->pb_decreaseLoad->setEnabled(true);
    ui->lbl_currentProtocol->setText(MANUAL_STRING);
}

void MainWindow::timer_seconds_timeout()
{
    time = time.addMSecs(TIMER_SECONDS_PERIOD_MSEC);
    if (protocol.getId() != MANUAL)
    {
        stage_t stage = protocol.getStageFromTime(time);
        load = stage.getLoad();
        if (stage.getId() == 0)
        {
            on_pb_stop_clicked();
        }
    }
    ui->lbl_timeValue->setText(time.toString("hh:mm:ss"));
    ui->lbl_loadValue->setText(QString::number(load));
    sendLoad(load);
}

void MainWindow::timer_com_timeout()
{
    parseSerial(RS232_PollComport(SERIAL_PORT_NUMBER, buf, SERIAL_BUFFER_LENGTH));
    ui->lbl_frequencyValue->setText(QString::number(rpm));
    ui->lbl_torqueValue->setText(QString::number(torque, 'f', 2));
}

void MainWindow::widget_destroyed()
{
    database = saveFileParser.download(SAVE_FILE);
    selection = database.getSelection();
    protocol.setId(selection);
    if (selection == MANUAL)
    {
        ui->lbl_currentProtocol->setText(MANUAL_STRING);
        ui->pb_manual->setEnabled(false);
        ui->pb_increaseLoad->setEnabled(true);
        ui->pb_decreaseLoad->setEnabled(true);
    }
    else
    {
        ui->lbl_currentProtocol->setText("Programa " + QString::number(selection));
        ui->pb_manual->setEnabled(true);
        ui->pb_increaseLoad->setEnabled(false);
        ui->pb_decreaseLoad->setEnabled(false);
        protocol = database.getProtocol(selection);
    }
}
