/*
 * IHM_REV2: database.cpp
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

/* =======================================================================
 * Includes
 * ======================================================================= */

#include "database.h"

/* =======================================================================
 * Constructors and Destructors
 * ======================================================================= */

database_t::database_t(){}

/* =======================================================================
 * Public Functions
 * ======================================================================= */

QVector<protocol_t>* database_t::getProtocolVector()
{
    return &protocolVector;
}

protocol_t database_t::getProtocol(unsigned int id)
{
    unsigned int len = protocolVector.size();
    for (unsigned int i = 0; i < len; i++)
    {
        if (protocolVector[i].getId() == id)
        {
            return protocolVector[i];
        }
    }
    protocol_t protocol;
    return protocol;
}

void database_t::addProtocol(protocol_t protocol)
{
    protocolVector.push_back(protocol);
}

void database_t::addStage(unsigned int pid, stage_t stage)
{
    unsigned int len = protocolVector.size();
    for (unsigned int i = 0; i < len; i++)
    {
        if (protocolVector[i].getId() == pid)
        {
            protocolVector[i].getStageVector()->push_back(stage);
            break;
        }
    }
}

void database_t::editProtocol(protocol_t protocol)
{
    unsigned int id = protocol.getId();
    unsigned int len = protocolVector.size();
    for (unsigned int i = 0; i < len; i++)
    {
        if (protocolVector[i].getId() == id)
        {
            protocolVector[i] = protocol;
            break;
        }
    }
}

void database_t::editStage(protocol_t protocol, stage_t stage)
{
    unsigned int pid = protocol.getId();
    unsigned int sid = stage.getId();
    unsigned int plen = protocolVector.size();

    for (unsigned int i = 0; i < plen; i++)
    {
        if (protocolVector[i].getId() == pid)
        {
            QVector<stage_t>* stageVector = protocolVector[i].getStageVector();
            unsigned int slen = stageVector->size();
            for (unsigned int j = 0; j < slen; j++)
            {
                if ((*stageVector)[j].getId() == sid)
                {
                    (*stageVector)[j] = stage;
                    break;
                }
            }
        }
    }
}

bool database_t::protocolExists(unsigned int id)
{
    unsigned int len = protocolVector.size();
    for (unsigned int i = 0; i < len; i++)
    {
        if (protocolVector[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}

unsigned int database_t::getSelection()
{
    return selection;
}

void database_t::setSelection(unsigned int selection)
{
    this->selection = selection;
}
