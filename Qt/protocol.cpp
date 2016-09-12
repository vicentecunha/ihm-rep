/* =======================================================================
 * Includes
 * ======================================================================= */

#include "protocol.h"

/* =======================================================================
 * Constructors and Destructors
 * ======================================================================= */

protocol_t::protocol_t()
{
    this->id = MANUAL;
}

protocol_t::protocol_t(unsigned int id = MANUAL)
{
    this->id = id;
}

protocol_t::protocol_t(unsigned int id, QVector<stage_t> stageVector)
{
    this->id = id;
    this->stageVector = stageVector;
}

/* =======================================================================
 * Public Functions
 * ======================================================================= */

unsigned int protocol_t::getId()
{
    return id;
}

void protocol_t::setId(unsigned int id)
{
    this->id = id;
}

QVector<stage_t>* protocol_t::getStageVector()
{
    return &stageVector;
}

stage_t protocol_t::getStage(unsigned int id)
{
    unsigned int len = stageVector.size();
    for (unsigned int i = 0; i < len; i++)
    {
        if (stageVector[i].getId() == id)
        {
            return stageVector[i];
        }
    }
    stage_t stage;
    return stage;
}

bool protocol_t::stageExists(unsigned int id)
{
    unsigned int len = stageVector.size();
    for (unsigned int i = 0; i < len; i++)
    {
        if (stageVector[i].getId() == id)
        {
            return true;
        }
    }
    return false;
}

stage_t protocol_t::getStageFromTime(QTime time)
{
    QTime totalTime(0,0);
    unsigned int len = stageVector.size();
    for (unsigned int i = 1; i <= len; i++)
    {
        for (unsigned int j = 0; j < len; j++)
        {
            if (stageVector[j].getId() == i)
            {
                int secs = QTime(0,0).secsTo(stageVector[j].getTime());
                totalTime = totalTime.addSecs(secs);
                if (totalTime > time)
                {
                    return stageVector[j];
                }
            }
        }
    }
    stage_t stage;
    return stage;
}
