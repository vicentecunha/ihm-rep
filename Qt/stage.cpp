/*
 * IHM_REV2: stage.cpp
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

/* =======================================================================
 * Includes
 * ======================================================================= */

#include "stage.h"

/* =======================================================================
 * Constructors and Destructors
 * ======================================================================= */

stage_t::stage_t()
{
    this->id = 0;
}

stage_t::stage_t(unsigned int id = 0)
{
    this->id = id;
}

stage_t::stage_t(unsigned int id, unsigned int load, QTime time)
{
    this->id = id;
    this->load = load;
    this->time = time;
}

/* =======================================================================
 * Public Functions
 * ======================================================================= */

unsigned int stage_t::getId()
{
    return id;
}

unsigned int stage_t::getLoad()
{
    return load;
}

QTime stage_t::getTime()
{
    return time;
}

void stage_t::setId(unsigned int id)
{
    this->id = id;
}

void stage_t::setLoad(unsigned int load)
{
    this->load = load;
}

void stage_t::setTime(QTime time)
{
    this->time = time;
}
