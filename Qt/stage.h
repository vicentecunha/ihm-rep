#ifndef STAGE_H
#define STAGE_H

#include "constants.h"
#include <QTime>
#include <QXmlStreamAttributes>

class stage_t
{
public:
    stage_t();
    stage_t(unsigned int);
    stage_t(unsigned int, unsigned int, QTime);

    unsigned int getId();
    unsigned int getLoad();
    QTime getTime();
    void setId(unsigned int);
    void setLoad(unsigned int);
    void setTime(QTime);

private:
    unsigned int id;
    unsigned int load;
    QTime time;
};

#endif // STAGE_H
