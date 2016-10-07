/*
 * IHM_REV2: savefileparser.h
 *
 * Author: Vicente Cunha
 * Date: June 2016
 */

#ifndef SAVEFILEPARSER_H
#define SAVEFILEPARSER_H

#include "database.h"
#include "protocol.h"
#include "stage.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

class savefileparser_t
{
public:
    savefileparser_t();
    void openFile(QString);
    database_t download(QString);
    void upload(QString, database_t);

private:
    QFile file;
};

#endif // SAVEFILEPARSER_H
