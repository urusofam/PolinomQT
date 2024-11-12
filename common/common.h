#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    VAL_REQUEST = 1,
    VAL_ANSWER,
    ADD_ROOT,
    CHANGE_AN,
    CHANGE_SIZE,
    PRINT_CLASSIC,
    PRINT_CANONIC,
    CHANGE_ONE_ROOT,
    PRINT_ANSWER,
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif
