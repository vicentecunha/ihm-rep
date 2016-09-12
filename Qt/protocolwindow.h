#ifndef PROTOCOLWINDOW_H
#define PROTOCOLWINDOW_H

#include "constants.h"
#include "ui_protocolwindow.h"
#include "protocol.h"
#include "savefileparser.h"
#include <QFile>
#include <QTime>
#include <QWidget>

namespace Ui {
class protocolwindow;
}

class protocolwindow : public QWidget
{
    Q_OBJECT

public:
    explicit protocolwindow(QWidget *parent = 0);
    ~protocolwindow();

private:
    Ui::protocolwindow *ui;
    unsigned int protocolId;
    unsigned int stageId;
    unsigned int load;
    QTime time;
    savefileparser_t saveFileParser;
    database_t database;

private slots:
    void on_pb_increaseProtocol_clicked();
    void on_pb_decreaseProtocol_clicked();
    void on_pb_increaseStage_clicked();
    void on_pb_decreaseStage_clicked();
    void on_pb_increaseLoad_clicked();
    void on_pb_decreaseLoad_clicked();
    void on_pb_increaseMinutes_clicked();
    void on_pb_decreaseMinutes_clicked();
    void on_pb_increaseSeconds_clicked();
    void on_pb_decreaseSeconds_clicked();
    void on_pb_exit_clicked();
};

#endif // PROTOCOLWINDOW_H
