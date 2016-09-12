/* =======================================================================
 * Includes
 * ======================================================================= */

#include "mainwindow.h"

/* =======================================================================
 * Constructors and Destructors
 * ======================================================================= */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    protocol.setId(MANUAL);
    load = 5;
    paused = false;
    time.setHMS(0,0,0);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));

    ui->pb_stop->setEnabled(false);
    ui->pb_pause->setEnabled(false);
    ui->pb_manual->setEnabled(false);

    database = saveFileParser.download(SAVE_FILE);
    selection = database.getSelection();

    RS232_OpenComport(4, 9600, "8N1");
    QString test = "TESTE\r\n";
    unsigned char test2[10];
    memcpy(test2, test.toStdString().c_str(), test.size());
    RS232_SendBuf(4, test2, test.size());
}

MainWindow::~MainWindow()
{
    RS232_CloseComport(4);
    delete timer;
    delete ui;
}

/* =======================================================================
 * Signal Handlers
 * ======================================================================= */

void MainWindow::on_pb_increaseLoad_clicked()
{
    int newLoad = ui->cb_timesFive->isChecked() ? load + 5 : load + 1;
    load = (newLoad <= MAXLOAD_WATTS) ? newLoad : load;
    ui->lbl_loadValue->setText(QString::number(load));
}

void MainWindow::on_pb_decreaseLoad_clicked()
{
    int newLoad = ui->cb_timesFive->isChecked() ? load - 5 : load - 1;
    load = (newLoad >= MINLOAD_WATTS) ? newLoad : load;
    ui->lbl_loadValue->setText(QString::number(load));
}

void MainWindow::on_pb_play_clicked()
{
    timer->start(1000);
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
    timer->stop();
    paused = false;
    time.setHMS(0,0,0);
    ui->lbl_timeValue->setText(time.toString("hh:mm:ss"));
    load = MINLOAD_WATTS;
    ui->lbl_loadValue->setText(QString::number(load));

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
    timer->stop();
    paused = true;
    old_load = load;
    load = MINLOAD_WATTS;
    ui->lbl_loadValue->setText(QString::number(load));

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

void MainWindow::timer_timeout()
{
    time = time.addSecs(1);
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
