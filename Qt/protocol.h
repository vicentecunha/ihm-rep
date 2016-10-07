/*
 * IHM_REV2: protocol.h
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "constants.h"
#include "stage.h"
#include <QString>
#include <QXmlStreamAttributes>
#include <QVector>

#define MANUAL 0

class protocol_t
{
public:
    protocol_t();
    protocol_t(unsigned int);
    protocol_t(unsigned int, QVector<stage_t>);

    unsigned int getId();
    void setId(unsigned int);
    QVector<stage_t>* getStageVector();
    stage_t getStage(unsigned int);
    stage_t getStageFromTime(QTime);
    bool stageExists(unsigned int);

private:
    unsigned int id;
    QVector<stage_t> stageVector;
};

#endif // PROTOCOL_H
