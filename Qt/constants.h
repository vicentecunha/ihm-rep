#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const int MINLOAD_WATTS = 5;
const int MAXLOAD_WATTS = 400;
const unsigned int MAXPROTOCOLID = 128;
const unsigned int MAXSTAGEID = 128;
const QString SAVE_FILE = "IHM.sav";
const QString PROTOCOL_STRING = "protocol";
const QString STAGE_STRING = "stage";
const QString SELECTION_STRING = "selection";
const QString TIME_FORMAT = "mm:ss";
const QString DELIMITER = "#";
const QString MANUAL_STRING = "Manual";
const QString SERIAL_DEVICE = "/dev/ttyS4";

#endif // CONSTANTS_H
