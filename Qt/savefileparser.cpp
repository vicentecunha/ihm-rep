/*
 * IHM_REV2: savefileparser.cpp
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

/* =======================================================================
 * Includes
 * ======================================================================= */

#include "savefileparser.h"

/* =======================================================================
 * Constructors and Destructors
 * ======================================================================= */

savefileparser_t::savefileparser_t(){}

/* =======================================================================
 * Public Functions
 * ======================================================================= */

database_t savefileparser_t::download(QString fileName)
{
    database_t database;
    protocol_t protocol;
    stage_t stage;

    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return database; // failed to open file
    }

    QTextStream textStream(&file);
    while (!textStream.atEnd())
    {
        QString string = textStream.readLine();
        if (string.startsWith(PROTOCOL_STRING))
        {
            QStringList stringList = string.split(DELIMITER);
            protocol.setId(stringList.at(1).toInt());
            database.addProtocol(protocol);
        }
        else if (string.startsWith(STAGE_STRING))
        {
            QStringList stringList = string.split(DELIMITER);
            stage.setId(stringList.at(1).toInt());
            stage.setLoad(stringList.at(2).toInt());
            stage.setTime(QTime::fromString(stringList.at(3), TIME_FORMAT));
            database.addStage(protocol.getId(), stage);
        }
        else if (string.startsWith(SELECTION_STRING))
        {
            QStringList stringList = string.split(DELIMITER);
            database.setSelection(stringList.at(1).toInt());
        }
    }
    file.close();
    return database;
}

void savefileparser_t::upload(QString fileName, database_t database)
{
    file.setFileName(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return; // failed to open file
    }

    QTextStream textStream(&file);
    textStream << SELECTION_STRING;
    textStream << DELIMITER << QString::number(database.getSelection()) << endl;

    QVector<protocol_t>* protocolVector = database.getProtocolVector();
    unsigned int plen = protocolVector->size();
    for (unsigned int i = 0; i < plen; i++)
    {
        textStream << PROTOCOL_STRING;
        textStream << DELIMITER << QString::number((*protocolVector)[i].getId()) << endl;
        QVector<stage_t>* stageVector = (*protocolVector)[i].getStageVector();
        unsigned int slen = stageVector->size();
        for (unsigned int j = 0; j < slen; j++)
        {
            textStream << STAGE_STRING;
            textStream << DELIMITER << QString::number((*stageVector)[j].getId());
            textStream << DELIMITER << QString::number((*stageVector)[j].getLoad());
            textStream << DELIMITER << (*stageVector)[j].getTime().toString("mm:ss") << endl;
        }
    }
    textStream.flush();
    file.close();
}
