/*
 * IHM_REV2: protocolwindow.cpp
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

/* =======================================================================
 * Includes
 * ======================================================================= */

#include "protocolwindow.h"

/* =======================================================================
 * Constructors and Destructors
 * ======================================================================= */

protocolwindow::protocolwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::protocolwindow)
{
    ui->setupUi(this);

    database = saveFileParser.download(SAVE_FILE);
    if (database.getProtocolVector()->size() < 1)
    {
        protocol_t protocol(protocolId);
        database.addProtocol(protocol);
        stage_t stage(stageId, load, time);
        database.addStage(protocolId, stage);
    }
    else
    {
        protocolId = database.getSelection();
        stageId = 1;
        load = database.getProtocol(protocolId).getStage(stageId).getLoad();
        time = database.getProtocol(protocolId).getStage(stageId).getTime();
    }

    ui->lbl_protocol->setText("Programa " + QString::number(protocolId));
    ui->lbl_loadValue->setText(QString::number(load));
    ui->lbl_timeValue->setText(time.toString(TIME_FORMAT));
}

protocolwindow::~protocolwindow()
{
    delete ui;
}

/* =======================================================================
 * Signal Handlers
 * ======================================================================= */

void protocolwindow::on_pb_increaseProtocol_clicked()
{
    protocolId += (protocolId < MAXSTAGEID) ? 1 : 0;
    ui->lbl_protocol->setText("Programa " + QString::number(protocolId));
    stageId = 1;

    if (database.protocolExists(protocolId))
    {
        protocol_t protocol = database.getProtocol(protocolId);
        if (protocol.stageExists(stageId))
        {
            stage_t stage = protocol.getStage(stageId);
            load = stage.getLoad();
            time = stage.getTime();
        }
        else
        {
            load = MINLOAD_WATTS;
            time.setHMS(0,0,0);
            stage_t stage(stageId, load, time);
            database.addStage(protocolId, stage);
        }
    }
    else
    {
        protocol_t protocol(protocolId);
        database.addProtocol(protocol);
        load = MINLOAD_WATTS;
        time.setHMS(0,0,0);
        stage_t stage(stageId, load, time);
        database.addStage(protocolId, stage);
    }

    ui->lbl_stageValue->setText(QString::number(stageId));
    ui->lbl_loadValue->setText(QString::number(load));
    ui->lbl_timeValue->setText(time.toString(TIME_FORMAT));
}

void protocolwindow::on_pb_decreaseProtocol_clicked()
{
    protocolId -= (protocolId > 1) ? 1 : 0;
    ui->lbl_protocol->setText("Programa " + QString::number(protocolId));
    stageId = 1;

    if (database.protocolExists(protocolId))
    {
        protocol_t protocol = database.getProtocol(protocolId);
        if (protocol.stageExists(stageId))
        {
            stage_t stage = protocol.getStage(stageId);
            load = stage.getLoad();
            time = stage.getTime();
        }
        else
        {
            load = MINLOAD_WATTS;
            time.setHMS(0,0,0);
            stage_t stage(stageId, load, time);
            database.addStage(protocolId, stage);
        }
    }
    else
    {
        protocol_t protocol(protocolId);
        database.addProtocol(protocol);
        load = MINLOAD_WATTS;
        time.setHMS(0,0,0);
        stage_t stage(stageId, load, time);
        database.addStage(protocolId, stage);
    }

    ui->lbl_stageValue->setText(QString::number(stageId));
    ui->lbl_loadValue->setText(QString::number(load));
    ui->lbl_timeValue->setText(time.toString(TIME_FORMAT));
}

void protocolwindow::on_pb_increaseStage_clicked()
{
    stageId += (stageId < MAXSTAGEID) ? 1 : 0;
    protocol_t protocol = database.getProtocol(protocolId);
    if (protocol.stageExists(stageId))
    {
        stage_t stage = protocol.getStage(stageId);
        load = stage.getLoad();
        time = stage.getTime();
    }
    else
    {
        load = MINLOAD_WATTS;
        time.setHMS(0,0,0);
        stage_t stage(stageId, load, time);
        database.addStage(protocolId, stage);
    }

    ui->lbl_stageValue->setText(QString::number(stageId));
    ui->lbl_loadValue->setText(QString::number(load));
    ui->lbl_timeValue->setText(time.toString(TIME_FORMAT));
}

void protocolwindow::on_pb_decreaseStage_clicked()
{
    stageId -= (stageId > 1) ? 1 : 0;
    protocol_t protocol = database.getProtocol(protocolId);
    if (protocol.stageExists(stageId))
    {
        stage_t stage = protocol.getStage(stageId);
        load = stage.getLoad();
        time = stage.getTime();
    }
    else
    {
        load = MINLOAD_WATTS;
        time.setHMS(0,0,0);
        stage_t stage(stageId, load, time);
        database.addStage(protocolId, stage);
    }

    ui->lbl_stageValue->setText(QString::number(stageId));
    ui->lbl_loadValue->setText(QString::number(load));
    ui->lbl_timeValue->setText(time.toString(TIME_FORMAT));
}

void protocolwindow::on_pb_increaseLoad_clicked()
{
    unsigned int newLoad = ui->cb_loadTimesFive->isChecked() ? load + 5 : load + 1;
    load = (newLoad <= MAXLOAD_WATTS) ? newLoad : load;
    ui->lbl_loadValue->setText(QString::number(load));
    stage_t stage(stageId, load, time);
    database.editStage(protocolId, stage);
}

void protocolwindow::on_pb_decreaseLoad_clicked()
{
    unsigned int newLoad = ui->cb_loadTimesFive->isChecked() ? load - 5 : load - 1;
    load = (newLoad >= MINLOAD_WATTS) ? newLoad : load;
    ui->lbl_loadValue->setText(QString::number(load));
    stage_t stage(stageId, load, time);
    database.editStage(protocolId, stage);
}

void protocolwindow::on_pb_increaseMinutes_clicked()
{
    if (ui->cb_minTimesFive->isChecked())
    {
        if (time.minute() < 55)
        {
            time = time.addSecs(300);
        }
    }
    else
    {
        if (time.minute() < 59)
        {
            time = time.addSecs(60);
        }
    }
    ui->lbl_timeValue->setText(time.toString("mm:ss"));
    stage_t stage(stageId, load, time);
    database.editStage(protocolId, stage);
}

void protocolwindow::on_pb_decreaseMinutes_clicked()
{
    if (ui->cb_minTimesFive->isChecked())
    {
        if (time.minute() >= 5)
        {
            time.setHMS(0,time.minute() - 5, time.second());
        }
    }
    else
    {
        if (time.minute() >= 1)
        {
            time.setHMS(0,time.minute() - 1, time.second());
        }
    }
    ui->lbl_timeValue->setText(time.toString("mm:ss"));
    stage_t stage(stageId, load, time);
    database.editStage(protocolId, stage);
}

void protocolwindow::on_pb_increaseSeconds_clicked()
{
    if (ui->cb_secondsTimesFive->isChecked())
    {
        if (!(time.minute() == 59 && time.second() >= 55))
        {
            time = time.addSecs(5);
        }
    }
    else
    {
        if (!(time.minute() == 59 && time.second() >= 59))
        {
            time = time.addSecs(1);
        }
    }
    ui->lbl_timeValue->setText(time.toString("mm:ss"));
    stage_t stage(stageId, load, time);
    database.editStage(protocolId, stage);
}

void protocolwindow::on_pb_decreaseSeconds_clicked()
{
    if (ui->cb_secondsTimesFive->isChecked())
    {
        if (!(time.minute() == 0 && time.second() < 5))
        {
            if (time.second() < 5)
            {
                time.setHMS(0,time.minute() - 1, time.second() + 55);
            }
            else
            {
                time.setHMS(0,time.minute(), time.second() - 5);
            }
        }
    }
    else
    {
        if (!(time.minute() == 0 && time.second() < 1))
        {
            if (time.second() < 1)
            {
                time.setHMS(0,time.minute() - 1, time.second() + 59);
            }
            else
            {
                time.setHMS(0,time.minute(), time.second() - 1);
            }
        }
    }
    ui->lbl_timeValue->setText(time.toString("mm:ss"));
    stage_t stage(stageId, load, time);
    database.editStage(protocolId, stage);
}

void protocolwindow::on_pb_exit_clicked()
{
    database.setSelection(protocolId);
    saveFileParser.upload(SAVE_FILE, database);
    this->close();
}
