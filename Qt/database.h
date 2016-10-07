/*
 * IHM_REV2: database.h
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

#ifndef DATABASE_H
#define DATABASE_H

#include "protocol.h"
#include <QVector>

class database_t
{
public:
    database_t();
    QVector<protocol_t>* getProtocolVector();
    protocol_t getProtocol(unsigned int);
    void addProtocol(protocol_t);
    void addStage(unsigned int, stage_t);
    void editProtocol(protocol_t);
    void editStage(protocol_t, stage_t);
    bool protocolExists(unsigned int);
    unsigned int getSelection();
    void setSelection(unsigned int);

private:
    QVector<protocol_t> protocolVector;
    unsigned int selection;

};

#endif // DATABASE_H
