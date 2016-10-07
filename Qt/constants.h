/*
 * IHM_REV2: constants.h
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const unsigned int MINLOAD_WATTS = 5;
const unsigned int MAXLOAD_WATTS = 400;
const unsigned int MAXPROTOCOLID = 128;
const unsigned int MAXSTAGEID = 128;
const QString SAVE_FILE = "IHM.sav";
const QString PROTOCOL_STRING = "protocol";
const QString STAGE_STRING = "stage";
const QString SELECTION_STRING = "selection";
const QString TIME_FORMAT = "mm:ss";
const QString DELIMITER = "#";
const QString MANUAL_STRING = "Manual";
const int SERIAL_PORT_NUMBER = 16; // ttyUSB0
const int SERIAL_PORT_BAUDRATE = 9600;
const int SERIAL_BUFFER_LENGTH = 4096;
const int TIMER_PERIOD_MSEC = 100;

#endif // CONSTANTS_H
